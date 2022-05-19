/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Evolution/EvolutionManager.h"

// Currently, the rank algorithm is:
// (20 - rank)^2,
// where a good rank is 0 and a bad rank is 19
int UEvolutionManager::GetRankDuplication(int Rank, int MaxRank)
{
    return (MaxRank - Rank) * (MaxRank - Rank);
}


// Sorts if A is greater than B
bool UEvolutionManager::SortByFitness (DNA A, DNA B)
{
	return A.StoredFitness > B.StoredFitness;
}


// Generates a new population with children
void UEvolutionManager::GeneratePopulation(TArray<DNA> Children)
{
	// Check if the number of children is empty
	if (Children.Num() == 0)
	{
		// Adds in a new DNA strand
		for (int i = 0; i < NumPopulation; ++i)
			Population.Add(DNA(NumGenes));
	}

	// Otherwise, reset the population
	else
	{
		Population.Empty();
		Population.Append(Children);

		// Create the remainder of the DNA
		for (int i = 0; i <  - Children.Num(); ++i)
		{
			Population.Add(DNA(NumGenes));
		}
	}

	// Increase the number of generations
	NumGenerations++;
}


// Creates the next generation of children
TArray<DNA> UEvolutionManager::CreateChildGeneration()
{
	// Get a list of children to output
	TArray<DNA> NewChildren;

	// Create an array that lists all the indexes of the selected DNA,
	// where the first rank has more in the array than the second and
	// so on. Assume that the population has already been sorted.
	TArray<int> RankingIndex;
	for (int Rank = 0; Rank < NumSelectedParents; ++Rank)
		for (int i = 0; i < GetRankDuplication(Rank, NumSelectedParents); ++i)
			RankingIndex.Add(Rank);

	// Loop through the number of children to evolve
	for (int i = 0; i < FRACTION_RANDOM_CHILDREN * NumPopulation; ++i)
	{
		// Pick two random values for the ranking
		const int RandomIndexA = RankingIndex[FMath::RandRange(0, RankingIndex.Num() - 1)];
		const int RandomIndexB = RankingIndex[FMath::RandRange(0, RankingIndex.Num() - 1)];

		// Find two parents based on these indexes
		DNA ParentA = Population[RandomIndexA];
		const DNA ParentB = Population[RandomIndexB];

		// Create a child
		DNA Child = ParentA.Crossover(ParentB);

		// Check if should mutate the child's genes
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHANCE)
		{
			// Mutate the child
			Child.Mutation();
		}

		// Adds the child to the list
		NewChildren.Add(Child);
	}

	// Return the final list of children
	return NewChildren;
}


// Sets up all the new parameters
void UEvolutionManager::Initialize(int Genes, int PopulationSize, int SelectedParents)
{
	// Update the population and number of genes each of the evolutions have.
	NumGenes = Genes;
	NumPopulation = PopulationSize;
	NumSelectedParents = FMath::Min(SelectedParents, PopulationSize);

	// Empty the populations
	Population.Empty();
	DeadDNA.Empty();

	// Generate an empty population with no children
	GeneratePopulation();
}


// Evolves the simulation of population
void UEvolutionManager::Evolve()
{
	// Sort the population by fitness
	Population.Sort(&SortByFitness);

	// Get the new child generation
	const TArray<DNA> Children = CreateChildGeneration();

	// Generate the new population
	GeneratePopulation(Children);
}


DNA UEvolutionManager::RetrieveDNA()
{
	// Ensure there are remaining DNA
	if (Population.Num() > 0)
	{
		// Get the current DNA
		DNA NewDNA = Population[0];
		Population.RemoveAt(0);
		return NewDNA;
	}

	// If there were no DNA remaining, create a new one.
	// This should in theory never happen if coded correctly.
	UE_LOG(LogTemp, Error, TEXT("Unable to find any more DNA when Retrieving DNA."));
	return DNA(NumGenes);
}


void UEvolutionManager::AddDeadDNA(DNA Dead)
{
	// Adds the new DNA to the dead list
	DeadDNA.Add(Dead);
}


void UEvolutionManager::GenerationEnd(float Time, TArray<DNA> AlivePopulation)
{
	// The population should already be empty, but in case it is not
	Population.Empty();

	// Add the new population to the list
	Population.Append(AlivePopulation);

	// Add the Dead DNA to the list of population
	Population.Append(DeadDNA);

	// Empty the current Dead DNA list
	DeadDNA.Empty();

	// Add the time to the generation and reset
	GenerationDeathTimes.Add(Time);

	// Sort the population based on fitness
	Population.Sort(&SortByFitness);

	// Add the best and median population fitness
	GenerationBestFitness.Add(Population[0].StoredFitness);
	GenerationMedianFitness.Add(Population[NumPopulation * 0.5f].StoredFitness);
}
