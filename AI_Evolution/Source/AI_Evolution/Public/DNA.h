/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

/**
 * @brief The class that handles the DNA storing data about the
 * genes of the agents.
 */
class AI_EVOLUTION_API DNA
{
	/*************************************************************/
	public:

	// The chance of mutation
	static constexpr float MUTATION_CHANCE = 0.05f;

	// The number of strength values
	int NumOfStrengthValues;

	// The list of strength values
	TArray<float> StrengthValues;

	// The current fitness stored
	int StoredFitness = -1;
	

	/*************************************************************/
	public:
	
	/**
	 * @brief Base constructor with no parameters
	 */
	DNA();
	
	/**
	 * @brief Constructs a new DNA with a specific size
	 * @param DNASize The size of the DNA
	 */
	DNA(int DNASize);

	/**
	 * @brief Destructor of the DNA
	 */
	~DNA();

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
