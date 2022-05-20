/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Evolution/DNA.h"

DNA::DNA()
{
	// This is only called when the data object is created.
	// This should not be called by the appropriate Ship Spawner manager.
}


// Main constructor with the number of genes
DNA::DNA(int DNASize)
{
	// Update the size of the fixed-length genome (this will not change for this simulation)
	NumOfStrengthValues = DNASize;

	// Randomises the genes
	Randomise();
}


// Merges a DNA with another
DNA DNA::Crossover (DNA Other)
{
	// Creates a new DNA
	DNA NewDNA = DNA(NumOfStrengthValues);

	// The minimum value for crossover
	constexpr int MinVal = 2;
	const int MidIndex = FMath::RandRange(MinVal, NumOfStrengthValues - MinVal);

	// Go through all the strength values
	for (int i = 0; i < NumOfStrengthValues; ++i)
	{
		// If using this gene
		if (i < MidIndex)
			NewDNA.StrengthValues[i] = StrengthValues[i];

		// If using the other gene
		else
			NewDNA.StrengthValues[i] = Other.StrengthValues[i];
	}

	// Return the new DNA
	return NewDNA;
}


// Mutates the current DNA strand
void DNA::Mutation()
{
	// Loop through every one of the strength values for mutations
	for (int i = 0; i < NumOfStrengthValues; ++i)
	{
		// If mutating this gene
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHANCE)
		{
			// Calculate the min and max for the random
			const float MinStrength = StrengthValues[i] * (1 - MUTATION_FACTOR);
			const float MaxStrength = StrengthValues[i] * (1 + MUTATION_FACTOR);
			
			// Adjust the value ot a new random one
			StrengthValues[i] = FMath::RandRange(MinStrength, MaxStrength);

			// Clamp the value within the bounds
			StrengthValues[i] = FMath::Clamp(StrengthValues[i], MIN_STRENGTH_VALUE, MAX_STRENGTH_VALUE);
		}
	}
}


// Randomises all values
void DNA::Randomise()
{
	// Empty the current list
	StrengthValues.Empty();
	
	// Randomise between min and max all the strengths
	for (int i = 0; i < NumOfStrengthValues; ++i)
		StrengthValues.Add(FMath::RandRange(MIN_STRENGTH_VALUE, MAX_STRENGTH_VALUE));
}


// Sets the default values
void DNA::SetDefault(TArray<float> Default)
{
	// Ensures the length matches
	if (Default.Num() != NumOfStrengthValues)
		return;

	// Updates the list with these elements
	StrengthValues.Empty();
	StrengthValues.Append(Default);
}
