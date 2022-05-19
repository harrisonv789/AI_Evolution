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

	// Create the evolution managers for each of the species
	HarvesterEvolution = NewObject<UEvolutionManager>(this);

	// Initialise all of the evolution managers
	HarvesterEvolution->Initialize(6, MaxShipCount, 20);

	// Spawn the initial ships
	for(int i = 0; i < MaxShipCount; i++)
	{
		SpawnHarvester();
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
	if (NumOfShips < MaxShipCount * SHIP_EVOLVE_CUTOFF)
	{
		// The current alive harvesters from the world
		TArray<AActor*> AliveHarvesters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoid::StaticClass(), AliveHarvesters);
		
		// Clear the population of DNA
		TArray<DNA> AlivePopulation;

		// Loop through all the alive harvesters
		for (const auto Ship : AliveHarvesters)
		{
			// Add the current population to the list
			ABoid* Boid = Cast<ABoid>(Ship);

			// Calculate the fitness scores of all alive ships
			Boid->CalculateAndStoreFitness(NONE);

			// Get the current population DNA
			AlivePopulation.Add(Boid->GetDNA());
		}

		// Find the current best ship of the previous generation 
		FindBestShipData();

		// Reset the population
		HarvesterEvolution->GenerationEnd(GenerationAliveTime, AlivePopulation);
		
		// Reset the current generation time
		GenerationAliveTime = 0.0;

		// Clear the dead statistics
		DeadStatistics.Empty();

		// Evolve the population
		HarvesterEvolution->Evolve();

		// Loop through all the alive harvesters
		for (const auto Ship : AliveHarvesters)
		{
			// Updates the DNA to the current population
			Cast<ABoid>(Ship)->ReplaceDNA();
		}
	
		// Spawn more ships
		while (NumOfShips < MaxShipCount)
		{
			SpawnHarvester();
		}
	}
}


// Spawns a new harvester ship into the world
void AShipSpawner::SpawnHarvester()
{
	// Randomise the location of the ship to spawn
	const float XLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float YLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float ZLoc = FMath::RandRange(500.0f, 4500.0f);
	const FVector Location(XLoc, YLoc, ZLoc);

	// Spawn the ship
	ABoid* SpawnedShip = Cast<ABoid>(GetWorld()->SpawnActor(HarvestShip, &Location ,&FRotator::ZeroRotator));
	SpawnedShip->Spawner = this;

	// Updates the evolution manager associated with this ship
	SpawnedShip->EvolutionManager = HarvesterEvolution;

	// Adds the ship to the list of alive ships
	AliveShips.Add(SpawnedShip);

	// Update the DNA of the Ship to a new one from the evolution
	SpawnedShip->ReplaceDNA();

	// Update the number of ships that exist
	NumOfShips++;
}


// Determines the best ship in the system
void AShipSpawner::FindBestShipData()
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


void AShipSpawner::RemoveShip(ABoid* Ship)
{
	// Subtract the number of ships
	NumOfShips--;

	// Add the ship's statistics
	DeadStatistics.Add(Ship->ShipStatistics);
	
	// Removes this ship from the list
	AliveShips.Remove(Ship);
}


TArray<AGasCloud*> AShipSpawner::GetGasClouds()
{
	return GasClouds;
}
