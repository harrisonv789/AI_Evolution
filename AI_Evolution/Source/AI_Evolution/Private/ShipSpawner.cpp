/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "ShipSpawner.h"

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

	// If the number of ships is less than 20% of the maximum
	if (NumOfShips < MaxShipCount * 0.2)
	{
		// Spawn more ships
		while(NumOfShips < MaxShipCount)
		{
			SpawnShip();
		}
	}
}


void AShipSpawner::SpawnShip()
{
	// Randomise the location
	const float XLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float YLoc = FMath::RandRange(-2000.0f, 2000.0f);
	const float ZLoc = FMath::RandRange(500.0f, 4500.0f);
	const FVector Location(XLoc, YLoc, ZLoc);

	// Spawn the ship
	ABoid* SpawnedShip = Cast<ABoid>(GetWorld()->SpawnActor(HarvestShip, &Location ,&FRotator::ZeroRotator));
	SpawnedShip->Spawner = this;

	// Update the variables
	SetShipVariables(SpawnedShip);
	NumOfShips++;
}


void AShipSpawner::SetShipVariables(ABoid* Ship)
{
	
}
