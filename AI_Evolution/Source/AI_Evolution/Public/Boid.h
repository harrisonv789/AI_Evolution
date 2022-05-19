/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "DeathReason.h"
#include "DNA.h"
#include "EvolutionManager.h"
#include "GasCloud.h"
#include "ShipDataContainer.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

// Forward declarations
class USphereComponent;
class AShipSpawner;

#define GOLDEN_RATIO 1.6180339

/**
 * @brief This class handles the Bird-like actors that are able to move
 * around the map with some functionality.
 */
UCLASS(Blueprintable, BlueprintType)
class AI_EVOLUTION_API ABoid : public AActor
{
	GENERATED_BODY()

	/*************************************************************/
	protected:

	// The minimum speed in units / s
	float MinSpeed = 300.0f;

	// The maximum speed in units / s
	float MaxSpeed = 600.0f;

	// The current DNA of the ship
	DNA ShipDNA;
	
	// The cloud that the ship is correctly collided with
	UPROPERTY()
	AGasCloud* CollisionCloud;

	// The ships velocity
	FVector BoidVelocity;

	// The ships rotation
	FRotator CurrentRotation;

	// Vision properties
	float SeparationFOV = -1.0f;
	float AlignmentFOV = 0.5f;
	float CohesionFOV = -0.5f;

	// Avoidance Sensors
	TArray<FVector> AvoidanceSensors;

	// The distances away that a sensor can reach
	float SensorRadius = 600.0f;

	// The number of sensors
	int NumSensors = 100;


	/*************************************************************/
	// EVOLUTIONARY PROPERTIES
	/*************************************************************/
	
	// The strength of the velocity matching of the BOIDS
	float VelocityStrength = 1.0f;

	// The strength to apply the separation between BOIDS
	float SeparationStrength = 1.0f;

	// The strength to apply to centering the flock
	float CenteringStrength = 1.0f;

	// The strength to apply between avoiding obstacles
	float AvoidanceStrength = 1.0f;

	// The strength to apply when traversing gas clouds
	float GasCloudStrength = 1.0f;

	// The additional speed strength to add to maximum
	float SpeedStrength = 1.0f;

	

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

	// The factor to apply for the time alive on the fitness function
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FitnessTimeWeighting = 0.5f;

	// The factor to apply for the gold on the fitness function
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FitnessGoldWeighting = 5.0f;
	
	// The maximum time being invincible
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxInvincibility = 0.1;

	// The current time being invincible
	UPROPERTY(BlueprintReadOnly)
	float Invincibility = 0.0;

	// The current time alive
	UPROPERTY(BlueprintReadOnly)
	float CurrentAliveTime = 0.0;

	// The number of gold collected so far
	UPROPERTY(BlueprintReadOnly)
	float GoldCollected = 0.0f;

	// The reference to the current spawner of the ship
	UPROPERTY()
	AShipSpawner* Spawner;

	// The current ship statistics related to the ship's life
	UPROPERTY(VisibleAnywhere)
	FShipDataContainer ShipStatistics;

	// The current evolution manager associated with this ship.
	UPROPERTY()
	UEvolutionManager* EvolutionManager;

	

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
	 * @brief Attempts to target the nearest gas clouds on the ship's quest to get gold.
	 * This adds up all forces of nearby gas clouds and attempts to move towards a
	 * specific one.
	 * @return An additional force
	 */
	FVector GasTargeting () const;
	
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
	 * @brief This method is executed when the ship dies, for a particular reason
	 * specified in the death reason. It will then calculate the fitness for the gene
	 * and clean up any values required.
	 * @param Reason The cause of the Ship's death
	 */
	void Death (EDeathReason Reason);

	

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
	 * @brief Sets the current DNA properties to a new DNA from the
	 * Evolution Manager of the ship. It takes the top one from the
	 * list and updates it's current DNA to that element. This ensures
	 * that the Ship Spawners do not need to deal with setting the Ship's
	 * own new DNA after an evolution has taken place.
	 */
	void ReplaceDNA ();

	/**
	 * @brief Returns the Ship's current DNA
	 * @return The DNA of the Ship
	 */
	DNA GetDNA ();

	/**
	 * @brief Calculates a new fitness value and stores the fitness in the DNA
	 * @param Reason The cause of the death
	 */
	void CalculateAndStoreFitness (EDeathReason Reason);

	/**
	 * @brief Updates the statistics of the ship to the values
	 * of the current ship's lifetime.
	 */
	void UpdateStatistics ();
	
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
	
	/**
	 * @brief Returns the current fitness, ignoring any factors and assumes no death.
	 * @return The current fitness stored in the DNA
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentFitness ();
	
};