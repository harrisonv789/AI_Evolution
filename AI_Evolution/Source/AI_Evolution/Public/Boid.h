/**
 * FIT3094 ASSIGNMENT 2 - GOAL PLANNING
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "GasCloud.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

class USphereComponent;
class AShipSpawner;

UCLASS()
class AI_EVOLUTION_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//the ship static mesh component
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BoidMesh;
	
	//the ship collision component
	UPROPERTY(VisibleAnywhere)
	USphereComponent* BoidCollision;

	//the ship collision sensor
	UPROPERTY(VisibleAnywhere)
	USphereComponent* PerceptionSensor;

	//the ships velocity
	FVector BoidVelocity;

	//the ships rotation
	FRotator CurrentRotation;
	void UpdateMeshRotation();

	//Avoid crowding/collision with local Ships
	FVector	AvoidShips(TArray<AActor*> Flock);
	//return force directed towards the average heading of local Ships
	FVector VelocityMatching(TArray<AActor*> Flock);
	//return force directed toward the average position of local Ships
	FVector FlockCentering(TArray<AActor*> Flock);
	//apply to the ship and update movement
	void FlightPath(float DeltaTime);
	//checks if the ship is on a collision course with obstacle
	bool IsObstacleAhead();
	//return obstacle avoidance force steering towards the unobstructed direction
	FVector AvoidObstacle();

	protected:
	//list of forces
	TArray<FVector> GasCloudForces;
	float MinSpeed = 300.0f;
	float MaxSpeed = 600.0f;
	
public:
	//Strength Values to Alter with evolution
	float VelocityStrength = 100.0f;
	float SeparationStrength = 100.0f;
	float CenteringStrength = 1.0f;
	float AvoidanceStrength = 10000.0f;
	float GasCloudStrength = 1.0f;

	//Vision and Spawn Invincibility
	float SeparationFOV = -1.0f;
	float AlignmentFOV = 0.5f;
	float CohesionFOV = -0.5f;
	float Invincibility = 5.0f;
	
	//avoidance sensors
	TArray<FVector> AvoidanceSensors;
	float SensorRadius = 600.0f;
	int NumSensors = 100;
	//golden ratio constant used for spacing the packing points onto the sphere
	const float GoldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2;

	UPROPERTY(VisibleAnywhere)
		float GoldCollected = 0.0f;
	
	AGasCloud* CollisionCloud;
	AShipSpawner* Spawner;
	
	UFUNCTION()
		void OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor,  UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,  bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnHitboxOverlapEnd(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};