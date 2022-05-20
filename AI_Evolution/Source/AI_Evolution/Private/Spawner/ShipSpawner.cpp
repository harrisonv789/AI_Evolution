/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Spawner/ShipSpawner.h"
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
	PirateEvolution = NewObject<UEvolutionManager>(this);

	// Initialise all of the evolution managers
	HarvesterEvolution->Initialize(6, MaxHarvesterCount, 30);
	PirateEvolution->Initialize(5, MaxPirateCount, 6);

	// Spawn the initial ships and defaults
	for (int i = 0; i < MaxHarvesterCount; i++)
		SpawnShip(false)->SetDefaultGenes();
	for (int i = 0; i < MaxPirateCount; i++)
		SpawnShip(true)->SetDefaultGenes();

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

	// Ensure the pirate ships always exist
	while (NumPirates < MaxPirateCount)
	{
		SpawnShip(true);
	}

	// If the number of ships is less than 20% of the maximum
	if (NumHarvesters < MaxHarvesterCount * SHIP_EVOLVE_CUTOFF)
	{
		// The current alive harvesters from the world
		TArray<AActor*> AliveHarvesters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHarvesterBoid::StaticClass(), AliveHarvesters);
		
		// Clear the population of DNA
		TArray<DNA> AliveHarvesterPopulation;

		// Loop through all the alive harvesters
		for (const auto Ship : AliveHarvesters)
		{
			// Add the current population to the list
			ABoid* Boid = Cast<ABoid>(Ship);

			// Calculate the fitness scores of all alive ships
			Boid->CalculateAndStoreFitness(NONE);

			// Get the current population DNA
			AliveHarvesterPopulation.Add(Boid->GetDNA());
		}
		

		// The current alive harvesters from the world
		TArray<AActor*> AlivePirates;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APirateBoid::StaticClass(), AlivePirates);
		
		// Clear the population of DNA
		TArray<DNA> AlivePiratePopulation;

		// Loop through all the alive harvesters
		for (const auto Ship : AlivePirates)
		{
			// Add the current population to the list
			ABoid* Boid = Cast<ABoid>(Ship);

			// Calculate the fitness scores of all alive ships
			Boid->CalculateAndStoreFitness(NONE);

			// Get the current population DNA
			AlivePiratePopulation.Add(Boid->GetDNA());
		}

		// Find the current best ship of the previous generation 
		FindBestShipData();

		// Reset the population
		HarvesterEvolution->GenerationEnd(GenerationAliveTime, AliveHarvesterPopulation);
		PirateEvolution->GenerationEnd(GenerationAliveTime, AlivePiratePopulation);
		
		// Reset the current generation time
		GenerationAliveTime = 0.0;

		// Clear the dead statistics
		DeadStatistics.Empty();

		// Evolve the population
		HarvesterEvolution->Evolve();
		PirateEvolution->Evolve();

		// Loop through all the alive harvesters
		for (const auto Ship : AliveHarvesters)
		{
			// Updates the DNA to the current population
			Cast<ABoid>(Ship)->ReplaceDNA();
		}
	
		// Spawn more ships
		while (NumHarvesters < MaxHarvesterCount)
		{
			SpawnShip(false);
		}

		// Loop through all the alive pirates
		for (const auto Ship : AlivePirates)
		{
			// Updates the DNA to the current population
			Cast<ABoid>(Ship)->ReplaceDNA();
		}
	}
}


// Spawns a new harvester ship into the world
ABoid* AShipSpawner::SpawnShip(bool IsPirate)
{
	// Randomise the location of the ship to spawn
	const float XLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float YLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float ZLoc = FMath::RandRange(500.0f, 4500.0f);
	const FVector Location(XLoc, YLoc, ZLoc);

	// Spawn the ship (pirate or harvester)
	ABoid* SpawnedShip = Cast<ABoid>(GetWorld()->SpawnActor(IsPirate ? PirateShip : HarvestShip, &Location ,&FRotator::ZeroRotator));
	SpawnedShip->Spawner = this;

	// Updates the evolution manager associated with this ship
	SpawnedShip->EvolutionManager = IsPirate ? PirateEvolution : HarvesterEvolution;

	// Adds the ship to the list of alive ships
	AliveShips.Add(SpawnedShip);

	// If a pirate and the DNA already exists from the previous death, then replace
	if (IsPirate && DeadPirateDNA.Num() > 0)
	{
		// Get the DNA from the previous
		Cast<APirateBoid>(SpawnedShip)->SetDNA(DeadPirateDNA[0]);
		DeadPirateDNA.RemoveAt(0);
		
	} else
	{
		// Update the DNA of the Ship to a new one from the evolution
		SpawnedShip->ReplaceDNA();
	}

	// Update the number of ships that exist
	if (IsPirate)
		NumPirates++;
	else
		NumHarvesters++;

	// Return the spawned ship
	return SpawnedShip;
}


// Determines the best ship in the system
void AShipSpawner::FindBestShipData()
{
	// The best ship's fitness score
	float HarvesterBestShipFitness = -1;
	float PirateBestShipFitness = -1;

	// Find the best alive ship
	for (ABoid* Ship : AliveShips)
	{
		// If it is a pirate
		if (Ship->IsA(APirateBoid::StaticClass()))
		{
			// If the ship's fitness is greater than the current best
			if (Ship->GetCurrentFitness() > PirateBestShipFitness || PirateBestShipFitness < 0)
			{
				PirateBestShipFitness = Ship->GetCurrentFitness();
				BestPirateInGeneration = Ship->ShipStatistics;
			}
		}

		// Otherwise assume it is a harvester
		else
		{
			// If the ship's fitness is greater than the current best
			if (Ship->GetCurrentFitness() > HarvesterBestShipFitness || HarvesterBestShipFitness < 0)
			{
				HarvesterBestShipFitness = Ship->GetCurrentFitness();
				BestHarvesterInGeneration = Ship->ShipStatistics;
			}
		}
		
	}

	// The highest fitness could be a dead ship
	for (const FShipDataContainer Data : DeadStatistics)
	{
		// Check for if a pirate
		if (Data.IsPirate)
		{
			// If the ship's fitness is greater than the current best
			if (Data.Fitness > PirateBestShipFitness || PirateBestShipFitness < 0)
			{
				PirateBestShipFitness = Data.Fitness;
				BestPirateInGeneration = Data;
			}
		}

		// Otherwise a harvester
		else
		{
			// If the ship's fitness is greater than the current best
			if (Data.Fitness > HarvesterBestShipFitness || HarvesterBestShipFitness < 0)
			{
				HarvesterBestShipFitness = Data.Fitness;
				BestHarvesterInGeneration = Data;
			}
		}
		
	}
}


// Removes a ship from the list
void AShipSpawner::RemoveShip(ABoid* Ship)
{
	// If this is a pirate
	if (Ship->IsA(APirateBoid::StaticClass()))
	{
		// Add the dead pirate DNA
		const DNA PirateDNA = Ship->GetDNA();
		DeadPirateDNA.Add(PirateDNA);

		UE_LOG(LogTemp, Warning, TEXT("Pirate at 0: %d"), PirateDNA.StoredFitness);

		// Subtract the number of ships
		NumPirates--;
	}

	// Otherwise if a harvester
	else
	{
		// Subtract the number of ships
		NumHarvesters--;
	}

	// Removes this ship from the list
	AliveShips.Remove(Ship);

	// Add the ship's statistics
	DeadStatistics.Add(Ship->ShipStatistics);
}


// Gets the gas cloud array
TArray<AGasCloud*> AShipSpawner::GetGasClouds()
{
	return GasClouds;
}
