// Fill out your copyright notice in the Description page of Project Settings.

#include "Boid.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "ShipSpawner.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ABoid::ABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setup boid mesh component & attach to root
	BoidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boid Mesh Component"));
	RootComponent = BoidMesh;
	BoidMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoidMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	//setup boid collision component and set as root
	BoidCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Boid Collision Component"));
	BoidCollision->SetupAttachment(RootComponent);
	BoidCollision->SetCollisionObjectType(ECC_Pawn);
	BoidCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoidCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoidCollision->SetSphereRadius(30.0f);
	
	//setup cohesion sensor component
	PerceptionSensor = CreateDefaultSubobject<USphereComponent>(TEXT("Perception Sensor Component"));
	PerceptionSensor->SetupAttachment(RootComponent);
	PerceptionSensor->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PerceptionSensor->SetCollisionResponseToAllChannels(ECR_Ignore);
	PerceptionSensor->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PerceptionSensor->SetSphereRadius(300.0f);

	//set default velocity
	BoidVelocity = FVector::ZeroVector;

	//empty sensor array
	AvoidanceSensors.Empty();

	//theta angle of rotation on xy plane around z axis (yaw) around sphere

	//direction vector pointing from the center to point on sphere surface
	FVector SensorDirection;

	for (int32 i = 0; i < NumSensors; ++i)
	{
		//calculate the spherical coordinates of the direction vectors endpoint
		float yaw = 2 * UKismetMathLibrary::GetPI() * GoldenRatio * i;
		float pitch = FMath::Acos(1 - (2 * float(i) / NumSensors));

		//convert point on sphere to cartesian coordinates xyz
		SensorDirection.X = FMath::Cos(yaw)*FMath::Sin(pitch);
		SensorDirection.Y = FMath::Sin(yaw)*FMath::Sin(pitch);
		SensorDirection.Z = FMath::Cos(pitch);
		//add direction to list of sensors for avoidance
		AvoidanceSensors.Emplace(SensorDirection);
	}
}

// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();
	//set velocity based on spawn rotation and flock speed settings
	BoidVelocity = this->GetActorForwardVector();
	BoidVelocity.Normalize();
	BoidVelocity *= FMath::FRandRange(MinSpeed, MaxSpeed);

	BoidCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoid::OnHitboxOverlapBegin);
	BoidCollision->OnComponentEndOverlap.AddDynamic(this, &ABoid::OnHitboxOverlapEnd);
	
	//set current mesh rotation
	CurrentRotation = this->GetActorRotation();
}

// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//move ship
	FlightPath(DeltaTime);
	
	//update ship mesh rotation
	UpdateMeshRotation();

	if(CollisionCloud != nullptr)
	{
		GoldCollected += CollisionCloud->RemoveGold();
	}

	if(Invincibility > 0)
	{
		Invincibility -= DeltaTime;
	}
}

void ABoid::UpdateMeshRotation()
{
	//rotate toward current boid heading smoothly
	CurrentRotation = FMath::RInterpTo(CurrentRotation, this->GetActorRotation(), GetWorld()->DeltaTimeSeconds, 7.0f);
	this->BoidMesh->SetWorldRotation(CurrentRotation);
}

//-------------------------------------Lab 8 Starts Here-----------------------------------------------------------------------------

void ABoid::FlightPath(float DeltaTime)
{
	
}

FVector ABoid::AvoidShips(TArray<AActor*> NearbyShips)
{
	return FVector();
}

FVector ABoid::VelocityMatching(TArray<AActor*> NearbyShips)
{
	return FVector();
}

FVector ABoid::FlockCentering(TArray<AActor*> NearbyShips)
{
	return FVector();
}

FVector ABoid::AvoidObstacle()
{
	return FVector();
}



//------------------------------------------Collision Code---------------------------------------------------------------------------


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

void ABoid::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this && Invincibility <= 0)
	{
		AGasCloud* cloud = Cast<AGasCloud>(OtherActor);
		if (cloud != nullptr && OtherComponent->GetName().Equals(TEXT("Boid Collision Component")))
		{
			CollisionCloud = cloud;
			return;
		}
		
		ABoid* ship = Cast<ABoid>(OtherActor);
		if (ship != nullptr && OtherComponent->GetName().Equals(TEXT("Boid Collision Component")))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Collector Ship Collided With Ship"));
			Spawner->NumofShips--;
			Destroy();
			return;
		}
		
		AStaticMeshActor* wall = Cast<AStaticMeshActor>(OtherActor);
		if(wall != nullptr && OverlappedComponent->GetName().Equals(TEXT("Boid Collision Component")))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Collector Ship Collided With Wall"));
			Spawner->NumofShips--;
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
