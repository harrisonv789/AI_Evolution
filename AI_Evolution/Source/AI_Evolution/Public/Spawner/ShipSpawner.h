/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "Boids/Boid.h"
#include "Boids/HarvesterBoid.h"
#include "Boids/PirateBoid.h"
#include "Evolution/EvolutionManager.h"
#include "Environment/GasCloud.h"
#include "GameFramework/Actor.h"
#include "ShipSpawner.generated.h"

/**
 * @brief The default ship spawner class that handles spawning in ships
 * into the game world. The spawner does not handle any evolution of the
 * species in the world, as these are now created by the Evolution
 * Manager class that will evolve the ships. The managers are stored in
 * this instance and can be accessed to create a new generation of
 * ships.
 */
UCLASS(Blueprintable)
class AI_EVOLUTION_API AShipSpawner : public AActor
{
	GENERATED_BODY()

	/*************************************************************/

	// The factor to cut off the current population and re-evolve
	static constexpr float SHIP_EVOLVE_CUTOFF = 0.2f;


	/*************************************************************/

	// The current time the generation has been alive for
	float GenerationAliveTime = 0;

	// The current list of gas clouds spawned in the world
	UPROPERTY()
	TArray<AGasCloud*> GasClouds;

	// The current array of ships
	UPROPERTY()
	TArray<ABoid*> AliveShips;

	// The array of dead statistics
	TArray<FShipDataContainer> DeadStatistics;

	// The list of dead pirate DNA to take from
	TArray<DNA> DeadPirateDNA;

	
	/*************************************************************/
	public:

	// The maximum number of harvesters that must exist in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	int MaxHarvesterCount = 750;

	// The maximum number of pirates that must exist in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	int MaxPirateCount = 15;

	// The type of harvester ship to spawn in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<AHarvesterBoid> HarvestShip;

	// The type of pirate ship to spawn in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<APirateBoid> PirateShip;

	// The maximum number of gas clouds to spawn into the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	int MaxGasCloudCount = 10;

	// The class for the gas cloud to spawn
	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<AGasCloud> GasCloud;

	// The current number of harvester ships spawned
	UPROPERTY(BlueprintReadOnly)
	int NumHarvesters = 0;

	// The current number of pirate ships spawned
	UPROPERTY(BlueprintReadOnly)
	int NumPirates = 0;

	// The current highest fitness's harvester ship from previous generation
	UPROPERTY(BlueprintReadOnly)
	FShipDataContainer BestHarvesterInGeneration;

	// The current highest fitness's pirate ship from previous generation
	UPROPERTY(BlueprintReadOnly)
	FShipDataContainer BestPirateInGeneration;

	// The evolution manager for the harvester ships. This will
	//		handle the evolution for this particular species.
	UPROPERTY(BlueprintReadOnly)
	UEvolutionManager* HarvesterEvolution;

	// The evolution manager for the pirate ships. This will
	//		handle the evolution for this particular species.
	UPROPERTY(BlueprintReadOnly)
	UEvolutionManager* PirateEvolution;


	/*************************************************************/
	private:
	
	/**
	 * @brief Called when the game's execution first begins. This sets
	 * up the simulation and creates all of the ships, gas clouds and
	 * the evolution managers. All the BOIDs will be connected to their
	 * respective evolutions and the appropriate DNAs will be created.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Spawns a new harvester ship into the world. This will also
	 * set up its DNA from its appropriate Evolve Manager class. It will
	 * spawn somewhere within the walls of the world.
	 * @param IsPirate Whether to spawn the pirate ship, or a harvester.
	 * @return The ship that was spawned.
	 */
	ABoid* SpawnShip(bool IsPirate);

	/**
	 * @brief Finds the best ship out of all the alive ships and stores
	 * it as a variable. This can be retrieved from the UI and displayed
	 * on the screen to help debug issues.
	 */
	void FindBestShipData();
	
	
	/*************************************************************/
	public:
	
	/**
	 * @brief Default constructor that initialises the values. This does
	 * not perform any key actions, as these are handled on the Begin Play
	 * event.
	 */
	AShipSpawner();

	/**
	 * @brief Called every frame to update the spawner. The purpose of the Tick
	 * function for the ShipSpawner class is to check the current simulation
	 * and see if too many ships have been killed. If so, then it will call
	 * upon the evolution manager instances to evolve the species currently
	 * present and dead. It also keeps track of some key statistics and ensures
	 * that the pirates remain.
	 * @param DeltaTime [s] The time-step of the tick
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief This method is executed when a ship is killed and will be
	 * deleted from the game. This method should handle cleaning up the ship
	 * and updating any properties in the ship arrays.
	 * @param Ship The reference to the BOID ship that was destroyed
	 */
	void RemoveShip (ABoid* Ship);

	/**
	 * @brief This method retrieves the current gas clouds present in the
	 * scene. This can be called upon by the BOID class that is required
	 * to have a gas cloud parameter, which will allow the BOID to retrieve
	 * the list of clouds to track to the nearest.
	 * @return The current gas clouds present in the simulation.
	 */
	TArray<AGasCloud*> GetGasClouds ();
};
