/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "DNA.h"

DNA::DNA()
{
	// This is only called when the data object is created.
	// This should not be called by the appropriate Ship Spawner manager.
}

DNA::DNA(int DNASize)
{
	// Update the size of the fixed-length genome (this will not change for this simulation)
	NumOfStrengthValues = DNASize;

	// Initialises the DNA with some a random value for now
	StrengthValues = {
		FMath::RandRange(1.0f, 1000.0f),//100.0f,			// Velocity Strength
		FMath::RandRange(1.0f, 1000.0f),//100.0f,			// Separation Strength
		FMath::RandRange(1.0f, 1000.0f),//1.0f,				// Centering Strength
		10000.0f,														// Avoidance Strength
		FMath::RandRange(1.0f, 1000.0f),//1.0f,				// Gas Cloud Strength
		FMath::RandRange(1.0f, 1000.0f),//5000.0f 			// Speed Strength
	};
}


DNA::~DNA()
{
	// Currently no need for a destructor
}


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


// TODO: Explain how the mutation works
void DNA::Mutation()
{
	// Loop through every one of the strength values for mutations
	for (int i = 0; i < NumOfStrengthValues; ++i)
	{
		// If mutating this gene
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHANCE)
		{
			// The mutation adjustment %
			constexpr float MUTATION_ADJUSTMENT = 0.10f;

			// Calculate the min and max for the random
			const float MinStrength = StrengthValues[i] * (1 - MUTATION_ADJUSTMENT);
			const float MaxStrength = StrengthValues[i] * (1 + MUTATION_ADJUSTMENT);
			
			// Adjust the value ot a new random one
			StrengthValues[i] = FMath::RandRange(MinStrength, MaxStrength);

			// Clamp the value within the bounds
			StrengthValues[i] = FMath::Clamp(StrengthValues[i], MIN_STRENGTH_VALUE, MAX_STRENGTH_VALUE);
		}
	}
}


void DNA::operator=(const DNA& Other)
{
	// Makes a copy of the parameters
	NumOfStrengthValues = Other.NumOfStrengthValues;

	// The list of strength values
	StrengthValues = Other.StrengthValues;

	// The current fitness stored
	StoredFitness = Other.StoredFitness;
}
