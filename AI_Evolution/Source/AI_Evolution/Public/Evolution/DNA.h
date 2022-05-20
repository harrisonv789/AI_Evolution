/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

/**
 * @brief The class that handles the DNA storing data about the
 * genes of the agents. The DNA is a fixed-length genome structure
 * for handling a specific number of strength values. The number
 * of genes the DNA has is dependent on the species, but will not
 * change throughout the evolution time.
 */
class AI_EVOLUTION_API DNA
{
	/*************************************************************/

	// The chance of mutation for each individual gene
	static constexpr float MUTATION_CHANCE = 0.25f;

	// The minimum value for a strength
	static constexpr float MIN_STRENGTH_VALUE = 0.0f;

	// The maximum value for a strength
	static constexpr float MAX_STRENGTH_VALUE = 10000.0;

	
	/*************************************************************/
	public:

	// The number of strength values
	int NumOfStrengthValues = 0;

	// The list of strength values
	TArray<float> StrengthValues;

	// The current fitness stored
	float StoredFitness = -1;
	

	/*************************************************************/
	
	/**
	 * @brief Base constructor with no parameters. This will never
	 * be called to initialise the parameters, only when creating
	 * new data it will be called. The constructor with a particular
	 * DNA size should be the one that is executed.
	 */
	DNA ();
	
	/**
	 * @brief Constructs a new DNA with a specific size. This will be
	 * the fixed-length genome and it should set up the values to be some
	 * initial value, based on the species being evolved.
	 * @param DNASize The number of genes in the DNA.
	 */
	DNA (int DNASize);

	/**
	 * @brief Crosses over the DNA with another DNA strand, merging the
	 * two together. This is handled with a crossover point at somewhere
	 * between the two DNAs. For example, the first two genes could come
	 * from the current DNA and the next four could come from the other
	 * DNA being passed in. It will then create a new DNA with these
	 * values and return the result.
	 * @param Other The other DNA to crossover with.
	 * @return The resultant crossover DNA strand.
	 */
	DNA Crossover (DNA Other);

	/**
	 * @brief The mutation method will execute small changes on the genes
	 * present in this DNA that may make it better or worse for the fitness
	 * function. These changes could be to increase or decrease the genome
	 * values by a small percentage, and any number of mutations may occur.
	 * During a mutation, all six genes could mutate, or only one gene may
	 * mutate. This is randomised and the direction that they mutate in will
	 * also be random.
	 */
	void Mutation();

	/**
	 * @brief The randomise function sets the values of all of the gene strengths
	 * in the DNA to a random number between the minimum and maximum strengths
	 * of the gene. This ensures that some of the genes may start at a random value,
	 * which ensures that if this random value is actually an ideal set for a good
	 * fitness function, some may exist in the population with such strengths.
	 */
	void Randomise();

	/**
	 * @brief This method will set the DNA to a series of default strengths that
	 * may be passed in from a species that is using the DNA. This may ensure that
	 * at the beginning of the simulation, a particular species has optimal results
	 * and that they can be set using this function. This does not randomise the
	 * set.
	 * @param Default The default array of parameters that should be set.
	 */
	void SetDefault(TArray<float> Default);

	/**
	 * @brief This operator is called when setting on DNA to another. This
	 * should copy all of the DNA variables from one DNA to another and is
	 * able to ensure consistency with a data. This particular class almost
	 * acts as a struct, so the copy operator is required.
	 * @param Other The DNA to copy from.
	 */
	void operator=(const DNA& Other);
	
};
