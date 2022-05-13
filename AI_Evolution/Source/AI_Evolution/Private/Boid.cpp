/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Boid.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "ShipSpawner.h"

// Sets default values
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

	// Empty sensor array
	AvoidanceSensors.Empty();

	// Theta angle of rotation on xy plane around z axis (yaw) around sphere

	// Direction vector pointing from the center to point on sphere surface
	FVector SensorDirection;

	for (int32 i = 0; i < NumSensors; ++i)
	{
		// Calculate the spherical coordinates of the direction vectors endpoint
		const float Yaw = 2 * UKismetMathLibrary::GetPI() * GOLDEN_RATIO * i;
		const float Pitch = FMath::Acos(1 - 2 * static_cast<float>(i) / NumSensors);

		// Convert point on sphere to cartesian coordinates xyz
		SensorDirection.X = FMath::Cos(Yaw)*FMath::Sin(Pitch);
		SensorDirection.Y = FMath::Sin(Yaw)*FMath::Sin(Pitch);
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
	BoidVelocity *= FMath::FRandRange(MinSpeed, MaxSpeed);

	// Add in the events for the overlap components
	BoidCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoid::OnHitboxOverlapBegin);
	BoidCollision->OnComponentEndOverlap.AddDynamic(this, &ABoid::OnHitboxOverlapEnd);
	
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

	// If the current cloud is collided
	if (CollisionCloud != nullptr)
	{
		GoldCollected += CollisionCloud->RemoveGold();
	}

	// If invincibility still exists
	if (Invincibility > 0)
		Invincibility -= DeltaTime;
}


void ABoid::SetDNA(DNA NewDNA)
{
	// Sets the DNA
	ShipDNA = NewDNA;

	// Update the strengths
	VelocityStrength = ShipDNA.StrengthValues[0];
	SeparationStrength = ShipDNA.StrengthValues[1];
	CenteringStrength = ShipDNA.StrengthValues[2];
	AvoidanceStrength = ShipDNA.StrengthValues[3];
	GasCloudStrength = ShipDNA.StrengthValues[4];
	SpeedStrength = ShipDNA.StrengthValues[5];
}


DNA ABoid::GetDNA()
{
	return ShipDNA;
}


void ABoid::UpdateMeshRotation()
{
	// Rotate toward current boid heading smoothly
	CurrentRotation = FMath::RInterpTo(CurrentRotation, this->GetActorRotation(), GetWorld()->DeltaTimeSeconds, 7.0f);
	this->BoidMesh->SetWorldRotation(CurrentRotation);
}


void ABoid::FlightPath(float DeltaTime)
{
	// Set the initial acceleration
	FVector Acceleration = FVector::ZeroVector;

	// Update the position and rotation
	this->SetActorLocation(this->GetActorLocation() + BoidVelocity * DeltaTime);
	SetActorRotation(BoidVelocity.ToOrientationQuat());

	// Determine any nearby ships
	TArray<AActor*> NearbyShips;
	PerceptionSensor->GetOverlappingActors(NearbyShips, TSubclassOf<ABoid>());

	// Add in the three rules of Boids
	Acceleration += AvoidShips(NearbyShips);
	Acceleration += VelocityMatching(NearbyShips);
	Acceleration += FlockCentering(NearbyShips);

	// If there are obstacles
	if (IsObstacleAhead())
		Acceleration += AvoidObstacle();

	// Apply Gas Cloud forces
	for (int i = 0; i < Spawner->GasClouds.Num(); i++)
	{
		// Determine the difference between the gas clouds and the location of the boid and add a force
		// Only within a certain distance
		FVector Force = Spawner->GasClouds[i]->GetActorLocation() - GetActorLocation();
		if (Force.Size() < 1500)
			GasCloudForces.Add(Force);
	}

	// Loop through all of the gas cloud forces
	for (FVector GasCloudForce : GasCloudForces)
	{
		// Adds the force to the acceleration of the clouds
		GasCloudForce = GasCloudForce.GetSafeNormal() * GasCloudStrength;
		Acceleration += GasCloudForce;
		GasCloudForces.Remove(GasCloudForce);
	}

	// Update the final velocity
	BoidVelocity += Acceleration * DeltaTime;

	// Clamp the velocity between some speeds
	BoidVelocity = BoidVelocity.GetClampedToSize(MinSpeed, MaxSpeed + (SpeedStrength / 10000) * 300);
}


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
		Steering /= ShipCount;
		Steering.GetSafeNormal() -= this->BoidVelocity.GetSafeNormal();
		Steering *= SeparationStrength;
		return Steering;
	}

	// Return an empty vector otherwise
	return FVector::ZeroVector;
}


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
		Steering /= ShipCount;
		Steering.GetSafeNormal() -= this->BoidVelocity.GetSafeNormal();
		Steering *= VelocityStrength;
		return Steering;
	}

	// Otherwise return an empty vector
	return FVector::ZeroVector;
}


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
		AveragePosition /= ShipCount;
		FVector Steering = AveragePosition - this->GetActorLocation();
		Steering.GetSafeNormal() -= this->BoidVelocity.GetSafeNormal();
		Steering *= CenteringStrength;
		return Steering;
	}

	// Otherwise return an empty vector
	return FVector::ZeroVector;
}


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
			Steering *= AvoidanceStrength;
			return Steering;
		}
	}

	// Return an empty vector otherwise
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
		
		//line trace
		GetWorld()->LineTraceSingleByChannel(Hit,
			this->GetActorLocation(),
			this->GetActorLocation() + NewSensorDirection * SensorRadius,
			ECC_GameTraceChannel1,
			TraceParameters);

		//check if boid is inside object (i.e. no need to avoid/impossible to)
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


void ABoid::CalculateAndStoreFitness(EDeathReason Reason)
{
	// If the fitness is empty
	if (ShipDNA.StoredFitness < 0)
	{
		// First time calculating fitness
		// Add fitness calculation here

		// TODO: Replace this with a real calculation
		ShipDNA.StoredFitness = 0;
	}
}


void ABoid::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{

		// If currently not invincible and hitting a BOID collision
		if (Invincibility <= 0 && OtherComponent->GetName().Equals(TEXT("Boid Collision Component")))
		{
			// Get the cloud
			AGasCloud* Cloud = Cast<AGasCloud>(OtherActor);
			if (Cloud != nullptr)
			{
				CollisionCloud = Cloud;
				return;
			}

			// Check for a ship
			ABoid* Ship = Cast<ABoid>(OtherActor);
			if (Ship != nullptr)
			{
				// Subtract the number of ships
				Spawner->NumOfShips--;

				// Recalculates the fitness
				CalculateAndStoreFitness(SHIP_COLLISION);
				
				// Add the current ships' DNA to the dead DNA 
				Spawner->DeadDNA.Add(ShipDNA);

				// Destroy this ship
				Destroy();
				return;
			}
		}

		// If the other actor is a cube (like a wall that it collides with)
		if (OtherActor->GetName().Contains("Cube") &&
			OverlappedComponent->GetName().Equals(TEXT("Boid Collision Component")))
		{
			Spawner->NumOfShips--;

			// Recalculates the fitness
			CalculateAndStoreFitness(WALL_COLLISION);
			
			// Add the current ships' DNA to the dead DNA 
			Spawner->DeadDNA.Add(ShipDNA);

			// Destroy this ship
			Destroy();
		}
	}
}


void ABoid::OnHitboxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	AGasCloud* cloud = Cast<AGasCloud>(OtherActor);
	if (cloud != nullptr)
	{
		CollisionCloud = nullptr;
	}
}
