/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "GasCloud.h"
#include "GameFramework/Actor.h"
#include "ShipSpawner.generated.h"


/**
 * @brief The default ship spawner class that handles spawning in ships
 * into the game world. This spawner class also handles the evolution of
 * ships in the world. It evolves the ships after a certain amount of
 * ships are killed.
 */
UCLASS()
class AI_EVOLUTION_API AShipSpawner : public AActor
{
	GENERATED_BODY()

	/*************************************************************/
	private:
	
	// The number of parents
	static constexpr int NUM_PARENTS_PAIR = 50;

	// The chance for mutation
	static constexpr float MUTATION_CHANCE = 0.5;

	// The current time the generation has been alive for
	float GenerationAliveTime = 0;

	
	/*************************************************************/
	public:

	// The maximum number of ships that must exist in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	float MaxShipCount = 300;

	// The type of ship to spawn in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<ABoid> HarvestShip;

	// The maximum number of gas clouds to spawn into the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	float MaxGasCloudCount = 5;

	// The class for the gas cloud to spawn
	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<AGasCloud> GasCloud;

	// The current number of ships spawned
	UPROPERTY(BlueprintReadOnly)
	int NumOfShips = 0;

	// The number of generations
	UPROPERTY(BlueprintReadOnly)
	int NumGenerations = 0;

	// The current highest fitness's ship from previous generation
	UPROPERTY(BlueprintReadOnly)
	FShipDataContainer BestShipInGeneration;

	// The current list of gas clouds spawned in the world
	UPROPERTY()
	TArray<AGasCloud*> GasClouds;

	// The current Population of DNA
	TArray<DNA> Population;

	// The current array of ships
	UPROPERTY()
	TArray<ABoid*> AliveShips;

	// The array of dead statistics
	TArray<FShipDataContainer> DeadStatistics;
	
	// The list of DNA from dead ships
	TArray<DNA> DeadDNA;

	// A list of times it took for the generation to die
	UPROPERTY(BlueprintReadOnly)
	TArray<float> GenerationDeathTimes;

	


	/*************************************************************/
	protected:
	
	/**
	 * @brief Called when the game's execution first begins
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Spawns a single ship into the world
	 */
	void SpawnShip();

	/**
	 * @brief Finds the best ship out of all the alive ships and stores
	 * it as a variable. This can be retrieved from the UI and displayed
	 * on the screen to help debug issues.
	 */
	void FindBestShip();

	/**
	 * @brief Generates a new population of Ships
	 * @param NewChildren The new children to generate if they exist
	 */
	void GeneratePopulation(TArray<DNA> NewChildren = TArray<DNA>());

	/**
	 * @brief Returns the child generation
	 * @return The child generation created
	 */
	TArray<DNA> ChildGeneration ();
	
	
	/*************************************************************/
	public:
	
	/**
	 * @brief Default constructor that initialises the values
	 */
	AShipSpawner();

	/**
	 * @brief Called every frame to update the spawner
	 * @param DeltaTime The time-step in seconds
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Updates the ship variables in the world
	 * @param Ship The ship to update
	 */
	void SetShipVariables(ABoid* Ship);

	/**
	 * @brief This method is executed when a ship is killed and will be
	 * deleted from the game. This method should handle cleaning up the ship
	 * and updating any properties in the ship arrays.
	 * @param Ship The reference to the BOID ship that was destroyed
	 */
	void RemoveShip (ABoid* Ship);
};
