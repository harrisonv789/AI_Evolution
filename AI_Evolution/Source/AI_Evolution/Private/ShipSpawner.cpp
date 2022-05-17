/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "ShipSpawner.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AShipSpawner::AShipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AShipSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Generate the Populations
	GeneratePopulation();

	// Spawn the initial ships
	for(int i = 0; i < MaxShipCount; i++)
	{
		SpawnShip();
	}

	// Spawn the gas cloud count
	for(int i = 0; i < MaxGasCloudCount; i++)
	{
		const float XLoc = FMath::RandRange(-2500.0f, 2500.0f);
		const float YLoc = FMath::RandRange(-2500.0f, 2500.0f);
		const float ZLoc = FMath::RandRange(0.0f, 5000.0f);
		const FVector Location(XLoc, YLoc, ZLoc);

		// Add the gas cloud to the world
		GasClouds.Add(Cast<AGasCloud>(GetWorld()->SpawnActor(GasCloud, &Location, &FRotator::ZeroRotator)));
	}
}


// Called every frame
void AShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Increase the generation alive time
	GenerationAliveTime += DeltaTime;

	// If the number of ships is less than 20% of the maximum
	if (NumOfShips < MaxShipCount * 0.2)
	{
		// The current alive harvesters from the world
		TArray<AActor*> AliveHarvesters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoid::StaticClass(), AliveHarvesters);

		// Generate the Next Generation
		// We have 2 lists (alive ships with DNA and a list of dead DNA)
		// ...

		// Clear the population
		Population.Empty();

		// Loop through all the alive harvesters
		for (const auto Ship : AliveHarvesters)
		{
			ABoid* Boid = Cast<ABoid>(Ship);
			Population.Add(Boid->GetDNA());

			// Calculate the fitness scores of all alive ships
			Boid->CalculateAndStoreFitness(NONE);
		}

		// Find the current best ship of the previous generation 
		FindBestShip();

		// Add the Dead DNA to the population
		Population.Append(DeadDNA);
		DeadDNA.Empty();

		// Clear the dead statistics
		DeadStatistics.Empty();

		// Add the time to the generation and reset
		GenerationDeathTimes.Add(GenerationAliveTime);
		GenerationAliveTime = 0.0;

		// Generate a new population with the child generation
		GeneratePopulation(ChildGeneration());

		// Loop through all the alive harvesters
		for (const auto Ship : AliveHarvesters)
		{
			// Updates the DNA to the current population
			Cast<ABoid>(Ship)->SetDNA(Population[0]);
			Population.RemoveAt(0);
		}
	
		// Spawn more ships
		while (NumOfShips < MaxShipCount)
		{
			SpawnShip();
		}
	}
}


void AShipSpawner::SpawnShip()
{
	// Randomise the location of the spawn
	const float XLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float YLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float ZLoc = FMath::RandRange(500.0f, 4500.0f);
	const FVector Location(XLoc, YLoc, ZLoc);

	// Spawn the ship
	ABoid* SpawnedShip = Cast<ABoid>(GetWorld()->SpawnActor(HarvestShip, &Location ,&FRotator::ZeroRotator));
	SpawnedShip->Spawner = this;
	AliveShips.Add(SpawnedShip);

	// Update the variables
	SetShipVariables(SpawnedShip);
	NumOfShips++;
}


void AShipSpawner::FindBestShip()
{
	// The best ship's fitness score
	float TempBestShipFitness = -1;

	// Find the best alive ship
	for (ABoid* Ship : AliveShips)
	{
		// If the ship's fitness is greater than the current best
		if (Ship->GetCurrentFitness() > TempBestShipFitness || TempBestShipFitness < 0)
		{
			TempBestShipFitness = Ship->GetCurrentFitness();
			BestShipInGeneration = Ship->ShipStatistics;
		}
	}

	// The highest fitness could be a dead ship
	for (const FShipDataContainer Data : DeadStatistics)
	{
		// If the ship's fitness is greater than the current best
		if (Data.Fitness > TempBestShipFitness || TempBestShipFitness < 0)
		{
			TempBestShipFitness = Data.Fitness;
			BestShipInGeneration = Data;
		}
	}
}


void AShipSpawner::GeneratePopulation(TArray<DNA> NewChildren)
{
	// Check if the number of children is empty
	if (NewChildren.Num() == 0)
	{
		// Adds in a new DNA strand
		for (int i = 0; i < MaxShipCount; ++i)
			Population.Add(DNA(6));
	}

	// Otherwise, reset the population
	else
	{
		Population.Empty();
		Population.Append(NewChildren);

		// Create the remainder of the DNA
		for (int i = 0; i < MaxShipCount - NewChildren.Num(); ++i)
			Population.Add(DNA(6));
	}

	// Increase the number of generations
	NumGenerations++;
}



TArray<DNA> AShipSpawner::ChildGeneration()
{
	// Get a list of parents
	TArray<DNA> Parents;

	// Loop through the number of parents
	for (int i = 0; i < NUM_PARENTS_PAIR * 2; ++i)
	{
		// Store the current Highest fitness and index
		int TempHighestFitness = -1;
		int DNAIndex = -1;

		// Go through the population
		for (int j = 0; j < Population.Num(); ++j)
		{
			if (Population[j].StoredFitness > TempHighestFitness)
			{
				TempHighestFitness = Population[j].StoredFitness;
				DNAIndex = j;
			}
		}

		// If a new higher DNA is found
		if (DNAIndex >= 0)
		{
			// Found the highest fitness
			Parents.Add(Population[DNAIndex]);

			// Remove parents from population
			Population.RemoveAt(DNAIndex);
		}
	}

	// Create children array and set up to be added to population
	TArray<DNA> NewChildren;

	// Go through all the parents pairs
	for (int i = 0; i < NUM_PARENTS_PAIR; ++i)
	{
		// Ensure this value exists
		if (i * 2 + 1 >= NUM_PARENTS_PAIR)
			continue;
		
		// Only cross over with the top parents
		// This is Elitism
		DNA ChildOne = Parents[i * 2 + 0].Crossover(Parents[1]);
		UE_LOG(LogTemp, Warning, TEXT("%d"), ChildOne.StoredFitness);
		DNA ChildTwo = Parents[i * 2 + 1].Crossover(Parents[0]);

		// Mutate them
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHANCE)
		{
			// Pick which child to mutate
			if (FMath::RandBool())
				ChildOne.Mutation();
			else
				ChildTwo.Mutation();
		}

		// Add the new children to the list
		NewChildren.Add(ChildOne);
		NewChildren.Add(ChildTwo);
	}

	// Return the children
	return NewChildren;
}


void AShipSpawner::SetShipVariables(ABoid* Ship)
{
	// If the population exists
	if (Population.Num() > 0)
	{
		// Update the ship's DNA
		Ship->SetDNA(Population[0]);
		Population.RemoveAt(0);
	}

	// If there is not enough DNA, create a new one
	else
	{
		Ship->SetDNA(DNA(6));
	}
}


void AShipSpawner::RemoveShip(ABoid* Ship)
{
	// Subtract the number of ships
	NumOfShips--;

	// Add the ship's statistics
	DeadStatistics.Add(Ship->ShipStatistics);
				
	// Add the current ships' DNA to the dead DNA 
	DeadDNA.Add(Ship->GetDNA());
	
	// Removes this ship from the list
	AliveShips.Remove(Ship);
}
