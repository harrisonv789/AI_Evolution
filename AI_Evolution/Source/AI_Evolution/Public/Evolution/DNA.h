/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

/**
 * @brief The class that handles the DNA storing data about the
 * genes of the agents. The DNA is a fixed-length genome structure
 * for handling a specific number of strength values.
 */
class AI_EVOLUTION_API DNA
{
	/*************************************************************/
	public:

	// The chance of mutation for each individual gene
	static constexpr float MUTATION_CHANCE = 0.25f;

	// The minimum value for a strength
	static constexpr float MIN_STRENGTH_VALUE = 0.0f;

	// The maximum value for a strength
	static constexpr float MAX_STRENGTH_VALUE = 100000.0;

	// The number of strength values
	int NumOfStrengthValues = 0;

	// The list of strength values
	TArray<float> StrengthValues;

	// The current fitness stored
	float StoredFitness = -1;
	

	/*************************************************************/
	
	/**
	 * @brief Base constructor with no parameters
	 */
	DNA ();
	
	/**
	 * @brief Constructs a new DNA with a specific size
	 * @param DNASize The size of the DNA
	 */
	DNA (int DNASize);

	/**
	 * @brief Destructor of the DNA
	 */
	~DNA ();

	/**
	 * @brief Crosses over the DNA with another DNA creating a mutation
	 * @param Other The other DNA to crossover with
	 * @return The resultant crossover
	 */
	DNA Crossover (DNA Other);

	/**
	 * @brief Mutates the current genes in the DNA
	 */
	void Mutation();

	/**
	 * @brief Copies a DNA across
	 * @param Other The DNA to copy
	 * @return The new DNA
	 */
	void operator=(const DNA& Other);
	
};