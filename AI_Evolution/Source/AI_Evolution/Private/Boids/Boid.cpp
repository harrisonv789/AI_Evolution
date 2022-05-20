/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Boids/Boid.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Spawner/ShipSpawner.h"

// Sets default values on constructor
ABoid::ABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup boid mesh component & attach to root
	BoidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boid Mesh Component"));
	RootComponent = BoidMesh;
	BoidMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoidMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	// Setup boid collision component and set as root
	BoidCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Boid Collision Component"));
	BoidCollision->SetupAttachment(RootComponent);
	BoidCollision->SetCollisionObjectType(ECC_Pawn);
	BoidCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoidCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoidCollision->SetSphereRadius(30.0f);
	
	// Setup cohesion sensor component
	PerceptionSensor = CreateDefaultSubobject<USphereComponent>(TEXT("Perception Sensor Component"));
	PerceptionSensor->SetupAttachment(RootComponent);
	PerceptionSensor->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PerceptionSensor->SetCollisionResponseToAllChannels(ECR_Ignore);
	PerceptionSensor->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PerceptionSensor->SetSphereRadius(300.0f);

	// Set default velocity
	BoidVelocity = FVector::ZeroVector;

	// Set the invincibility time
	Invincibility = MaxInvincibility;

	// Empty sensor array
	AvoidanceSensors.Empty();

	// Direction vector pointing from the center to point on sphere surface
	FVector SensorDirection;

	// Initialise the sensors
	for (int32 i = 0; i < NumSensors; ++i)
	{
		// Calculate the spherical coordinates of the direction vectors endpoint
		const float Yaw = 2 * UKismetMathLibrary::GetPI() * GOLDEN_RATIO * i;
		const float Pitch = FMath::Acos(1 - 2 * static_cast<float>(i) / NumSensors);

		// Convert point on sphere to cartesian coordinates xyz
		SensorDirection.X = FMath::Cos(Yaw) * FMath::Sin(Pitch);
		SensorDirection.Y = FMath::Sin(Yaw) * FMath::Sin(Pitch);
		SensorDirection.Z = FMath::Cos(Pitch);
		
		// Add direction to list of sensors for avoidance
		AvoidanceSensors.Emplace(SensorDirection);
	}
}


// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();
	
	// Set velocity based on spawn rotation and flock speed settings
	BoidVelocity = this->GetActorForwardVector();
	BoidVelocity.Normalize();
	BoidVelocity *= FMath::FRandRange(GetMinSpeed(), GetMaxSpeed());

	// Add in the events for the overlap components
	BoidCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoid::OnHitBoxOverlapBegin);
	
	// Set current mesh rotation
	CurrentRotation = this->GetActorRotation();
}


// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move ship with the flight path
	FlightPath(DeltaTime);
	
	// Update ship mesh rotation
	UpdateMeshRotation();

	// If invincibility still exists
	if (Invincibility > 0)
		Invincibility -= DeltaTime;

	// Otherwise, increase the alive time
	else
		CurrentAliveTime += DeltaTime;
}


// Replaces the DNA with a new one from the population
void ABoid::ReplaceDNA(bool RetrieveNew)
{
	// Sets the DNA to the new DNA if required
	if (RetrieveNew) ShipDNA = EvolutionManager->RetrieveDNA();

	// Update the strengths from the DNA
	VelocityStrength = ShipDNA.StrengthValues[0];
	SeparationStrength = ShipDNA.StrengthValues[1];
	CenteringStrength = ShipDNA.StrengthValues[2];
	AvoidanceStrength = ShipDNA.StrengthValues[3];
	GasCloudStrength = ShipDNA.StrengthValues[4];

	// Reset the current alive time
	CurrentAliveTime = 0.0;

	// Reset the current gold count
	GoldCollected = 0.0;
}


// Retrieves the DNA
DNA ABoid::GetDNA()
{
	return ShipDNA;
}


// Updates the statistic information struct
void ABoid::UpdateStatistics()
{
	// Update the general information
	ShipStatistics.TimeAlive = CurrentAliveTime;

	// Update the strength values
	ShipStatistics.StrengthAlignment = VelocityStrength;
	ShipStatistics.StrengthAvoidance = AvoidanceStrength;
	ShipStatistics.StrengthCentering = CenteringStrength;
	ShipStatistics.StrengthSeparation = SeparationStrength;
	ShipStatistics.StrengthGasCloud = GasCloudStrength;

	// Update the gold value
	ShipStatistics.Gold = GoldCollected;

	// Calculate the fitness
	ShipStatistics.Fitness = GetCurrentFitness();

	// Ensure the statistics is valid
	ShipStatistics.IsValid = true;
}


// Updates the rotation to face the velocity
void ABoid::UpdateMeshRotation()
{
	// Rotate toward current boid heading smoothly
	CurrentRotation = FMath::RInterpTo(CurrentRotation, this->GetActorRotation(), GetWorld()->DeltaTimeSeconds, 7.0f);
	this->BoidMesh->SetWorldRotation(CurrentRotation);
}


// Returns thew ship filtering
TSubclassOf<AActor> ABoid::GetShipFilter()
{
	return TSubclassOf<ABoid>();
}


// Create the flight path
void ABoid::FlightPath(float DeltaTime)
{
	// Update the position and rotation from the previous frame
    this->SetActorLocation(this->GetActorLocation() + BoidVelocity * DeltaTime);
    SetActorRotation(BoidVelocity.ToOrientationQuat());

	// Set the initial acceleration
	FVector Acceleration = FVector::ZeroVector;

	// Determine any nearby ships from the sensor
	TArray<AActor*> NearbyShips;
	PerceptionSensor->GetOverlappingActors(NearbyShips, GetShipFilter());

	// Add in the three rules of Boids
	Acceleration += AvoidShips(NearbyShips).GetSafeNormal() * SeparationStrength;;
	Acceleration += VelocityMatching(NearbyShips).GetSafeNormal() * VelocityStrength;
	Acceleration += FlockCentering(NearbyShips).GetSafeNormal() * CenteringStrength;

	// Add in any additional forces
	Acceleration += AdditionalForce();

	// If there are obstacles
	if (IsObstacleAhead())
		Acceleration += AvoidObstacle().GetSafeNormal() * AvoidanceStrength;

	// Adds the force to the acceleration of the cloud targeting
	Acceleration += GasTargeting().GetSafeNormal() * GasCloudStrength;

	// Update the final velocity
	BoidVelocity += Acceleration * DeltaTime;

	// Clamp the velocity between some speeds
	BoidVelocity = BoidVelocity.GetClampedToSize(GetMinSpeed(), GetMaxSpeed());
}


// Avoids nearby ships
FVector ABoid::AvoidShips(TArray<AActor*> NearbyShips)
{
	// Initialise the local variables for the tracking of nearby ships
	FVector Steering = FVector::ZeroVector;
	int ShipCount = 0;
	FVector SeparationDirection = FVector::ZeroVector;

	// Look through all the ships
	for (AActor* OverlapActor : NearbyShips)
	{
		// Get the boid
		ABoid* LocalShip = Cast<ABoid>(OverlapActor);

		// Check if the ship exists
		if (LocalShip != nullptr && LocalShip != this)
		{
			// Check if Local Ship is outside the perception FOV
			if (FVector::DotProduct(this->GetActorForwardVector(),
				(LocalShip->GetActorLocation() - this->GetActorLocation()).GetSafeNormal()) <= SeparationFOV)
			{
				// LocalShip is outside the perception - skip
				continue;
			}

			// Get Normalized direction from the nearby ship
			SeparationDirection = this->GetActorLocation() - LocalShip->GetActorLocation();
			SeparationDirection = SeparationDirection.GetSafeNormal() * 2.0;

			// Get the scaling factor based on the other ship's proximity. 0 is far, 1 is close
			const float ProximityFactor = 1.0f - SeparationDirection.Size() / this->PerceptionSensor->GetScaledSphereRadius();

			// Add Steering force of the ship and increase the flock amount
			Steering += ProximityFactor * SeparationDirection;
			ShipCount++;
		}
	}

	// If the number of ships is greater than zero
	if (ShipCount > 0)
	{
		// Get the flock average separation force and apply a steering strength
		Steering /= static_cast<float>(ShipCount);
		Steering = Steering.GetSafeNormal();
		Steering -= this->BoidVelocity.GetSafeNormal();
		return Steering;
	}

	// Return an empty vector otherwise
	return FVector::ZeroVector;
}


// Matches the velocity of nearby ships
FVector ABoid::VelocityMatching(TArray<AActor*> NearbyShips)
{
	// Initialise the variables
	FVector Steering = FVector::ZeroVector;
	int ShipCount = 0;

	// Loop through each of the nearby ships
	for (AActor* OverlapActor : NearbyShips)
	{
		// Get the boid
		ABoid* LocalShip = Cast<ABoid>(OverlapActor);

		// Check if the ship exists
		if (LocalShip != nullptr && LocalShip != this)
		{
			// Check if Local Ship is outside the perception FOV
			if (FVector::DotProduct(this->GetActorForwardVector(),
				(LocalShip->GetActorLocation() - this->GetActorLocation()).GetSafeNormal()) <= SeparationFOV)
			{
				// LocalShip is outside the perception - skip
				continue;
			}

			// Add the LocalShip's alignment force
			Steering += LocalShip->BoidVelocity.GetSafeNormal();
			ShipCount++;
		}
	}

	// If the number of ships exist
	if (ShipCount > 0)
	{
		// Get the steering force as the average of the flocking direction
		Steering /= static_cast<float>(ShipCount);
		Steering = Steering.GetSafeNormal();
		Steering -= this->BoidVelocity.GetSafeNormal();
		return Steering;
	}

	// Otherwise return an empty vector
	return FVector::ZeroVector;
}


// Moves to the center of the flock
FVector ABoid::FlockCentering(TArray<AActor*> NearbyShips)
{
	int ShipCount = 0;
	FVector AveragePosition = FVector::ZeroVector;

	// Loop through each of the nearby ships
	for (AActor* OverlapActor : NearbyShips)
	{
		// Get the boid
		ABoid* LocalShip = Cast<ABoid>(OverlapActor);

		// Check if the ship exists
		if (LocalShip != nullptr && LocalShip != this)
		{
			// Check if Local Ship is outside the perception FOV
			if (FVector::DotProduct(this->GetActorForwardVector(),
				(LocalShip->GetActorLocation() - this->GetActorLocation()).GetSafeNormal()) <= SeparationFOV)
			{
				// LocalShip is outside the perception - skip
				continue;
			}

			// Get the Cohesive force to group with LocalShip
			AveragePosition += LocalShip->GetActorLocation();
			ShipCount++;
		}
	}

	// If the number of ships exist
	if (ShipCount > 0)
	{
		// Average Cohesion force of ships
		AveragePosition /= static_cast<float>(ShipCount);
		FVector Steering = AveragePosition - this->GetActorLocation();
		Steering = Steering.GetSafeNormal();
		Steering -= this->BoidVelocity.GetSafeNormal();
		return Steering;
	}

	// Otherwise return an empty vector
	return FVector::ZeroVector;
}


// Avoids obstacles
FVector ABoid::AvoidObstacle()
{
	FVector Steering = FVector::ZeroVector;
	FQuat SensorRotation = FQuat::FindBetweenVectors(AvoidanceSensors[0], this->GetActorForwardVector());
	FVector NewSensedDirection = FVector::ZeroVector;
	FHitResult Hit;

	// Look through the sensors
	for (FVector AvoidanceSensor : AvoidanceSensors)
	{
		// The hit parameters
		FCollisionQueryParams TraceParameters;
		
		// Check the trace
		NewSensedDirection = SensorRotation.RotateVector(AvoidanceSensor);
		GetWorld()->LineTraceSingleByChannel(Hit,
			this->GetActorLocation(),
			this->GetActorLocation() + NewSensedDirection * SensorRadius,
			ECC_GameTraceChannel1,
			TraceParameters);

		// If there is a hit
		if (!Hit.bBlockingHit)
		{
			Steering = NewSensedDirection.GetSafeNormal() - this->BoidVelocity.GetSafeNormal();
			return Steering;
		}
	}

	// Return an empty vector otherwise
	return FVector::ZeroVector;
}


// Targets the gas clouds
FVector ABoid::GasTargeting() const
{
	// Apply Gas Cloud forces
	FVector Steering;

	// Get the gas clouds present
	const TArray<AGasCloud*> GasClouds = Spawner->GetGasClouds();
	
	for (int i = 0; i < GasClouds.Num(); i++)
	{
		// Determine the difference between the gas clouds and the location of the boid and add a force.
		// Only within a certain distance from the cloud.
		FVector Force = GasClouds[i]->GetActorLocation() - GetActorLocation();
		if (Force.Size() < 1500)
		{
			Steering += Force;
		}
	}

	// Returns the steering vector
	return Steering;
}


// Additional force; empty in this class
FVector ABoid::AdditionalForce()
{
	return FVector::ZeroVector;
}


bool ABoid::IsObstacleAhead()
{
	if (AvoidanceSensors.Num() > 0)
	{
		FQuat SensorRotation = FQuat::FindBetweenVectors(AvoidanceSensors[0], this->GetActorForwardVector());
		FVector NewSensorDirection = FVector::ZeroVector;
		NewSensorDirection = SensorRotation.RotateVector(AvoidanceSensors[0]);
		FCollisionQueryParams TraceParameters;
		FHitResult Hit;
		
		// Line trace
		GetWorld()->LineTraceSingleByChannel(Hit,
			this->GetActorLocation(),
			this->GetActorLocation() + NewSensorDirection * SensorRadius,
			ECC_GameTraceChannel1,
			TraceParameters);

		// Check if boid is inside object (i.e. no need to avoid/impossible to)
		if (Hit.bBlockingHit)
		{
			TArray<AActor*> OverlapActors;
			BoidCollision->GetOverlappingActors(OverlapActors);
			for (AActor* OverlapActor : OverlapActors)
			{
				if (Hit.Actor == OverlapActor)
				{
					return false;
				}
			}
		}
		
		return Hit.bBlockingHit;
	}
	
	return false;
}


// Gets the minimum speed of the BOID
float ABoid::GetMinSpeed()
{
	return MinSpeed;
}


// Gets the maximum speed of the BOID
float ABoid::GetMaxSpeed()
{
	return MaxSpeed;
}


// Calculates the new fitness value
void ABoid::CalculateAndStoreFitness(EDeathReason Reason)
{
	// Update the statistics
	UpdateStatistics();
}


// Called on death
void ABoid::Death(EDeathReason Reason)
{
	// Recalculates the fitness
	CalculateAndStoreFitness(Reason);

	// Add this DNA to the dead DNA list
	if (!ShipStatistics.IsPirate)
		EvolutionManager->AddDeadDNA(GetDNA());

	// Remove the Ship from the spawner
	Spawner->RemoveShip(this);

	// Destroy this ship
	Destroy();
}


// On collided with another trigger
void ABoid::OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If there is a physical collision
	if(OtherActor && OtherActor != this)
	{
		// If the other actor is a cube (like a wall that it collides with)
		if (OtherActor->GetName().Contains("Cube") &&
			OverlappedComponent->GetName().Equals(TEXT("Boid Collision Component")))
		{
			// Call the death function
			Death(WALL_COLLISION);
		}
	}
}


// Gets the current fitness
float ABoid::GetCurrentFitness()
{
	return GetDNA().StoredFitness;
}


// Gets the default values
void ABoid::SetDefaultGenes()
{
	// Update the information without retrieving a new DNA
	ReplaceDNA(false);
}
