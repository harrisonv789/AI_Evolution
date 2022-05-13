/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "DeathReason.h"
#include "DNA.h"
#include "GasCloud.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

// Forward declarations
class USphereComponent;
class AShipSpawner;

/**
 * @brief This class handles the Bird-like actors that are able to move
 * around the map with some functionality.
 */
UCLASS()
class AI_EVOLUTION_API ABoid : public AActor
{
	GENERATED_BODY()

	/*************************************************************/
	protected:

	// List of current gas cloud forces
    TArray<FVector> GasCloudForces;

	// The minimum speed in units / s
	float MinSpeed = 300.0f;

	// The maximum speed in units / s
	float MaxSpeed = 600.0f;

	// The current DNA of the ship
	DNA ShipDNA;

	

	/*************************************************************/
	public:
	
	// The ship static mesh component
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BoidMesh;
	
	// The ship collision component
	UPROPERTY(VisibleAnywhere)
	USphereComponent* BoidCollision;

	// The ship collision sensor
	UPROPERTY(VisibleAnywhere)
	USphereComponent* PerceptionSensor;

	// The ships velocity
	FVector BoidVelocity;

	// The ships rotation
	FRotator CurrentRotation;

	// Vision properties
	float SeparationFOV = -1.0f;
	float AlignmentFOV = 0.5f;
	float CohesionFOV = -0.5f;

	// The current time being invincible
	float Invincibility = 5.0f;
	
	// Avoidance Sensors
	TArray<FVector> AvoidanceSensors;

	// The distances away that a sensor can reach
	float SensorRadius = 600.0f;

	// The number of sensors
	int NumSensors = 100;
	
	// Golden ratio constant used for spacing the packing points onto the sphere
	const float GOLDEN_RATIO = (1.0f + FMath::Sqrt(5.0f)) / 2;

	// The number of gold collected so far
	UPROPERTY(VisibleAnywhere)
	float GoldCollected = 0.0f;
	
	// The cloud that the ship si correctly collided with
	UPROPERTY()
	AGasCloud* CollisionCloud;

	// The reference to the current spawner of the ship
	UPROPERTY()
	AShipSpawner* Spawner;


	
	/*************************************************************/
	// EVOLUTIONARY PROPERTIES
	/*************************************************************/
	
	// The strength of the velocity matching of the BOIDS
	float VelocityStrength = 100.0f;

	// The strength to apply the separation between BOIDS
	float SeparationStrength = 100.0f;

	// The strength to apply to centering the flock
	float CenteringStrength = 1.0f;

	// The strength to apply between avoiding obstacles
	float AvoidanceStrength = 10000.0f;

	// The strength to apply when traversing gas clouds
	float GasCloudStrength = 1.0f;

	// The additional speed strength to add to maximum
	float SpeedStrength = 5000.0f;
	

	/*************************************************************/
	protected:
	
	/**
	 * @brief Called when the game first starts executing
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Updates the mesh to face in the direction of the current velocity
	 */
	void UpdateMeshRotation();

	/**
	 * @brief Attempts to avoid other ships nearby and returns a force vector
	 * @param Flock The current array of ships
	 * @return An additional force
	 */
	FVector	AvoidShips(TArray<AActor*> Flock);

	/**
	 * @brief Attempts to match the velocity of nearby ships and returns a force vector
	 * @param Flock The current array of ships
	 * @return An additional force
	 */
	FVector VelocityMatching(TArray<AActor*> Flock);
	
	/**
	 * @brief Attempts to move towards a local center of nearby ships and returns a force vector
	 * @param Flock The current array of ships
	 * @return An additional force
	 */
	FVector FlockCentering(TArray<AActor*> Flock);

	/**
	 * @brief Attempts to avoid any obstacles around the ship and returns a force vector
	 * @return An additional force
	 */
	FVector AvoidObstacle();
	
	/**
	 * @brief Calculates a new flight path based on the force vectors
	 * @param DeltaTime The time-step in seconds
	 */
	void FlightPath(float DeltaTime);

	/**
	 * @brief Attempts to determine if an obstacle is ahead
	 * @return If an obstacle is ahead
	 */
	bool IsObstacleAhead();

	/**
	 * @brief Calculates a new fitness value and stores the fitness in the DNA
	 * @param Reason The cause of the death
	 */
	void CalculateAndStoreFitness (EDeathReason Reason);

	

	/*************************************************************/
	public:
	
	/**
	 * @brief The default constructor for the Boid class
	 */
	ABoid();

	/**
	 * @brief Called every frame to update the actor
	 * @param DeltaTime The time-step in seconds
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Sets the current DNA properties
	 * @param NewDNA The new DNA to update to
	 */
	void SetDNA (DNA NewDNA);

	/**
	 * @brief Returns the Ship's current DNA
	 * @return The DNA of the Ship
	 */
	DNA GetDNA ();
	
	/**
	 * @brief Called when the hit-box is overlapped
	 * @param OverlappedComponent	The current overlapped component
	 * @param OtherActor			The actor that is overlapping
	 * @param OtherComponent		The other actor's component that is overlapping
	 * @param OtherBodyIndex		The other actor's body index overlapping
	 * @param bFromSweep			Whether or not the overlapping is caused by a sweep detection
	 * @param SweepResult			The hit result from the collision
	 */
	UFUNCTION()
	void OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,  bool bFromSweep, const FHitResult& SweepResult);
	
	/**
		* @brief Called when the hit-box overlapping is complete
	 * @param OverlappedComponent	The current overlapped component
	 * @param OtherActor			The actor that is overlapping
	 * @param OtherComponent		The other actor's component that is overlapping
	 * @param OtherBodyIndex		The other actor's body index overlapping
	 */
	UFUNCTION()
	void OnHitboxOverlapEnd(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	
};