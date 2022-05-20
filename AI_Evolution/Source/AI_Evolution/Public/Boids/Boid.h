/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "Data/DeathReason.h"
#include "Evolution/DNA.h"
#include "Evolution/EvolutionManager.h"
#include "Environment/GasCloud.h"
#include "Data/ShipDataContainer.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

// Forward declarations
class USphereComponent;
class AShipSpawner;

// The Golden Ratio is used for spawning in the sensors.
#define GOLDEN_RATIO 1.6180339

/**
 * @brief This class handles the Bird-like actors that are able to move
 * around the map with some functionality. The BOIDs act as a species
 * that are able to evolve. They can move around the map using a series
 * of parameters, defined in their DNA. BOID's have three particular values:
 *		- Velocity Matching (with nearby BOIDs)
 *		- Separation (to nearby BOIDs)
 *		- Centering (to nearby clusters of BOIDs)
 * Additionally, these BOIDs may have a few other parameters based on the type
 * of BOID they are, ensuring they don't collide with walls or are able to
 * traverse the world for gas clouds, where they could collect gold or consume
 * other BOIDs.
 */
UCLASS(BlueprintType)
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
	
	// The maximum time being invincible
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxInvincibility = 0.1;

	// The current time being invincible
	UPROPERTY(BlueprintReadOnly)
	float Invincibility = 0.0;

	// The current time alive
	UPROPERTY(BlueprintReadOnly)
	float CurrentAliveTime = 0.0;

	// The amount of gold collected so far.
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
	 * @brief Called when the game first starts executing. This will initialise
	 * a first direction and set up any of the overlap condition functions to
	 * be mapped to the correct event call.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Updates the mesh to face in the direction of the current velocity.
	 * BOIDs only face in the direction they are moving, which is defined
	 * as their velocity.
	 */
	void UpdateMeshRotation();

	/**
	 * @brief This method returns the class that the flocking mechanism
	 * should be looking for. This ensures that the ships are correctly
	 * moved towards when attempting to flock. In most cases, this should
	 * be the base BOID class to avoid.
	 * @return The current filtering of the ships.
	 */
	virtual TSubclassOf<AActor> GetShipFilter ();

	/**
	 * @brief Attempts to avoid other ships nearby and returns a force vector.
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
	 * @brief Calculates a new flight path based on the force vectors. It will
	 * also multiply the strength values from the DNA to the current vector set
	 * and will determine the final velocity of the flight path and move the
	 * ship in the correct direction.
	 * @param DeltaTime [s] The time-step of the tick.
	 */
	void FlightPath(float DeltaTime);

	/**
	 * @brief Attempts to determine if an obstacle is ahead by checking all
	 * of the sensors and returns true if on exists. This only applies for
	 * the walls surrounding the map.
	 * @return If an obstacle is ahead.
	 */
	bool IsObstacleAhead();

	/**
	 * @brief This method returns the minimum speed that a BOID can
	 * move at. This may be different between different species of
	 * BOIDs as some may have a constant speed.
	 * @return [u/s] The minimum speed that a BOID can move at.
	 */
	virtual float GetMinSpeed ();

	/**
	 * @brief This method returns the maximum speed that a BOID
	 * can move at. This may adjust if there are additional values
	 * that exist in the DNA to affect the maximum speed of a BOID.
	 * @return [u/s] The maximum speed that a BOID can move at.
	 */
	virtual float GetMaxSpeed ();
	

	/*************************************************************/
	public:
	
	/**
	 * @brief The default constructor for the Boid class. This sets up
	 * all of the collision components and the sensor directions around
	 * the BOID. It also initialises the invincibility parameter,
	 * preventing a BOID from colliding in the first fraction of time
	 * in the simulation, since the level may not yet be loaded correctly.
	 */
	ABoid();

	/**
	 * @brief Called every frame to update the actor position and rotation.
	 * A new calculation of the flight path will be created and the rotation
	 * of the mesh will face the direction of travel. Additionally, the
	 * current time will increase, storing how long it has been alive for.
	 * @param DeltaTime [s] The time-step in of the tick
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Sets the current DNA properties to a new DNA from the
	 * Evolution Manager of the ship. It takes the top one from the
	 * list and updates it's current DNA to that element. This ensures
	 * that the Ship Spawners do not need to deal with setting the Ship's
	 * own new DNA after an evolution has taken place.
	 * @param RetrieveNew A flag for if retrieving a new DNA from the evolve manager.
	 */
	virtual void ReplaceDNA (bool RetrieveNew = true);

	/**
	 * @brief Returns the Ship's current DNA, whether alive or dead, which
	 * can be tracked by the evolve manager class.
	 * @return The current DNA of the Ship.
	 */
	DNA GetDNA ();

	/**
	 * @brief Calculates a new fitness value from the world and stores
	 * that value in the current DNA. The fitness calculation will be
	 * different for each of the BOID types and the values may change.
	 * Additionally, the cause of the death (if it did die) will alter
	 * the final fitness value.
	 * @param Reason The cause of the death.
	 */
	virtual void CalculateAndStoreFitness (EDeathReason Reason);

	/**
	 * @brief Updates the statistics of the ship to the values
	 * of the current ship's lifetime. These values are stored
	 * and retrieved by the spawner to display on the UI.
	 */
	virtual void UpdateStatistics ();
	
	/**
	 * @brief Called when the hit-box is overlapped. This will handle killing
	 * the BOID due to a collision, or potentially collecting gold if it is
	 * a gas cloud that has been overlapped.
	 * @param OverlappedComponent	The current overlapped component
	 * @param OtherActor			The actor that is overlapping
	 * @param OtherComponent		The other actor's component that is overlapping
	 * @param OtherBodyIndex		The other actor's body index overlapping
	 * @param bFromSweep			Whether or not the overlapping is caused by a sweep detection
	 * @param SweepResult			The hit result from the collision
	 */
	UFUNCTION()
	virtual void OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,  bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * @brief This method is executed when the ship dies, for a particular reason
	 * specified in the death reason. It will then calculate the fitness for the gene
	 * and clean up any values required.
	 * @param Reason The cause of the Ship's death
	 */
	void Death (EDeathReason Reason);
	
	/**
	 * @brief Returns the current fitness, ignoring any factors and assumes no death.
	 * This fitness is retrieved from the current DNA present on the BOID.
	 * @return The current fitness stored in the DNA.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentFitness ();

	/**
	 * @brief This function will set a series of default values to set the
	 * genes to. This will be called when the simulation first starts, and will
	 * initialise the DNA with a series of default values. The length of these
	 * strengths must be the same as the length of the genotype.
	 */
	virtual void SetDefaultGenes ();
	
};