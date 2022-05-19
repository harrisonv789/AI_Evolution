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
UCLASS(Blueprintable)
class AI_EVOLUTION_API AShipSpawner : public AActor
{
	GENERATED_BODY()

	/*************************************************************/
	private:

	// The factor to cut off the current population and re-evolve
	static constexpr float SHIP_EVOLVE_CUTOFF = 0.2f;

	// The number of selected DNA for evolving
	UPROPERTY(EditAnywhere, Category = "Entities")
	int NumSelectedParents = 20;
	
	// The number of children to evolve based on parental genes
	// The remainder have random gene values
	UPROPERTY(EditAnywhere, Category = "Entities")
	int NumEvolvedChildren = 300;

	// The chance for mutation
	UPROPERTY(EditAnywhere, Category = "Entities")
	float MutationChance = 0.9f;

	// The current time the generation has been alive for
	float GenerationAliveTime = 0;

	
	/*************************************************************/
	public:

	// The maximum number of ships that must exist in the world
	UPROPERTY(EditAnywhere, Category = "Entities")
	int MaxShipCount = 300;

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

	// A list of the best fitneses over the generations
	UPROPERTY(BlueprintReadOnly)
	TArray<float> GenerationBestFitness;

	// A list of fitness medians over the generations
	UPROPERTY(BlueprintReadOnly)
	TArray<float> GenerationMedianFitness;

	


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
	void FindBestShipData();

	/**
	 * @brief When determining the rank selection of the parents, the best
	 * fitness species should have a higher chance of replicating than the
	 * remainder. As such, this function determines how many times a particular
	 * rank should appear in the selection array based on the rank number, where
	 * 0 is the best and MaxRank is the 'worst' (but still in the top of the
	 * fitness values selected).
	 * @param Rank The rank to generate
	 * @param MaxRank The maximum rank of the list
	 * @return The number of times the rank should exist in the list
	 */
	static int GetRankDuplication (int Rank, int MaxRank);

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

	/**
	 * @brief A sorting function that returns whether the first DNA is greater
	 * than the second DNA. This is sent into the sorting algorithm to correctly
	 * sort between the Population based on the highest DNA. This can be done using
	 * the TArray::Sort function and passing in this as a reference.
	 * @param A The first DNA
	 * @param B The second DNA
	 * @return Whether the first DNA is greater than the second DNA
	 */
	static bool SortFitness (DNA A, DNA B);
	
	
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
