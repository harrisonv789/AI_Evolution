/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "DNA.h"
#include "EvolutionManager.generated.h"

/**
 * @brief This class handles the evolution of the simulation, including
 * for Harvesters and Pirates. The Evolution Manager is coupled with
 * the ShipSpawner class and is able to evolve the population with
 * a series of parameters. The population is evolved using a ranked
 * parental selection method, which is explained in more detail with
 * the provided documentation.
 */
UCLASS(Blueprintable)
class UEvolutionManager : public UObject
{
    GENERATED_BODY()

	/*************************************************************/

	// The fraction of children that are not evolved from parents. These
	//		will have random gene values.
	static constexpr float FRACTION_RANDOM_CHILDREN = 0.9f;

	// The chance that a new child will have a mutation in at least one of
	//		their genes.
	static constexpr float MUTATION_CHANCE = 0.9f;


	/*************************************************************/

	// The size of the gene to simulate. This is set in the initializer.
	int NumGenes;

	// The size of the population to simulate. This is set in the initializer.
	int NumPopulation;

	// The number of parents to select when evolving the system. This is set
	//		in the initializer.
	int NumSelectedParents;

	// The current Population of DNA that exists in the simulation.
	TArray<DNA> Population;

	// The current list of Dead DNA that exist in the simulation.
	//		These are added when ships die.
	TArray<DNA> DeadDNA;


	/*************************************************************/
	public:

	// The number of generations that have passed
	UPROPERTY(BlueprintReadOnly)
	int NumGenerations = 0;

	// A list of times it took for the generation to die.
	UPROPERTY(BlueprintReadOnly)
	TArray<float> GenerationDeathTimes;

	// A list of the best fitnesses over the generations
	UPROPERTY(BlueprintReadOnly)
	TArray<float> GenerationBestFitness;

	// A list of fitness medians over the generations.
	//		These values are taken as the worst of the alive ships
	//		at the end of the generation time.
	UPROPERTY(BlueprintReadOnly)
	TArray<float> GenerationMedianFitness;


	/*************************************************************/
	private:

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
	 * @brief A sorting function that returns whether the first DNA is greater
	 * than the second DNA. This is sent into the sorting algorithm to correctly
	 * sort between the Population based on the highest DNA. This can be done using
	 * the TArray::Sort function and passing in this as a reference.
	 * @param A The first DNA
	 * @param B The second DNA
	 * @return Whether the first DNA is greater than the second DNA
	 */
	static bool SortByFitness (DNA A, DNA B);
	
	/**
	 * @brief Generates a new population of DNA and fills up the current Population
	 * array with the new generation. It takes in a list of children to fill up
	 * the population with. If the population count does not reach the maximum
	 * amount for the population, then it will fill up with new DNA based on the starting
	 * values of the algorithm. More information can be found in the DNA class.
	 * @param Children The new children to generate if they exist
	 */
	void GeneratePopulation(TArray<DNA> Children = TArray<DNA>());

	/**
	 * @brief Creates a new generation of children based on the current population
	 * of parents. Currently, it selects the best [20] parents, ranked on the fitness
	 * calculation and randomly creates all children based on two random parents from
	 * the mix. Mutations and Crossovers will occur and all remaining children will
	 * be returned from the function.
	 * @return The child generation created.
	 */
	TArray<DNA> CreateChildGeneration ();


	/*************************************************************/
	public:
	
    /**
     * @brief This method sets up the important parameters surrounding the evolution
     * of the system, for one specific species type. This will set up how the genes will
     * be handled and any information that is required to be initialised. This should be
     * called when the simulation first begins and should not be changed during runtime.
     * @param Genes The number of genes to simulate for this evolution type.
     * @param PopulationSize The size of the population for this evolution type.
     * @param SelectedParents The number of parents to be selected when evolving
     *		the system.
     */
    void Initialize (int Genes, int PopulationSize, int SelectedParents);

    /**
     * @brief This method is called to execute an evolution. This will be called by
     * the ShipSpawner class and will be called on each species Evolution Manager.
     * This will reset the population, perform any evolutions that are necessary and
     * create any new DNA if required. This should be called at the end of a generation,
     * when a specific ship number threshold has been crossed and too few ships remain.
     */
    void Evolve ();

    /**
     * @brief Retrieves a new DNA from the current population that can be added to a
     * particular ship. After being retrieved, it is removed from the current population
     * array as it is added back into the ship's properties. The DNA will be added
     * into the population at the end of the generation time.
     * @return A new DNA from the population list.
     */
    DNA RetrieveDNA ();

    /**
     * @brief Adds in a new DNA from a ship that just died. The reason of the death
     * is not required here, but it simply adds the DNA to the current dead DNA list
     * so that it could be chosen as a potential parent if it is suitable enough.
     * This may require the fitness value to be extraordinarily high, due to the
     * negative fitness factor applied on ships that are killed. 
     * @param Dead A new DNA from a dead ship to add.
     */
    void AddDeadDNA (DNA Dead);

    /**
     * @brief Resets the population of the DNA to a new population, that have been
     * correctly updated with the new fitness values that were calculated during the
     * generation runtime. This method will be called when the generation has ended
     * and it is time to evolve the simulation of a particular species. Additionally,
     * the end generation time will be recorded in the list. This also updates the
     * current statistics of the population and stores them in the list. This function
     * does not evolve the next population, as that is called separately.
     * @param Time [s] The time taken for the generation to run for.
     * @param AlivePopulation The current alive population list to reset to.
     */
    void GenerationEnd (float Time, TArray<DNA> AlivePopulation);
	
};
