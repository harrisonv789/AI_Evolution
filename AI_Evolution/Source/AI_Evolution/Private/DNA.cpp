/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "DNA.h"

DNA::DNA()
{
	// Nothing
}


DNA::DNA(int DNASize)
{
	NumOfStrengthValues = DNASize;

	// Loop through all the Strength values
	for (int i = 0; i < NumOfStrengthValues; i++)
	{
		// Random strength
		StrengthValues.Add(FMath::RandRange(0.0f, 10000.0f));
	}
}


DNA::~DNA()
{
 
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
		{
			NewDNA.StrengthValues[i] = StrengthValues[i];
		}

		// If using the other gene
		else
		{
			NewDNA.StrengthValues[i] = Other.StrengthValues[i];
		}
	}

	// Return the new DNA
	return NewDNA;
}


void DNA::Mutation()
{
	// Array from 0 - 100,000
	for (int i = 0; i < NumOfStrengthValues; ++i)
	{
		// If mutating this gene
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHANCE)
		{
			// TODO: Need to improve this (maybe not new random, just adjust)
			StrengthValues[i] = FMath::RandRange(0, 100000);
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
