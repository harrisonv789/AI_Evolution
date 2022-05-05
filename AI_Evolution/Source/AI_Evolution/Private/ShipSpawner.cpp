// Fill out your copyright notice in the Description page of Project Settings.


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
	for(int i = 0; i < MaxShipCount; i++)
	{
		SpawnShip();
	}

	for(int i = 0; i < 5; i++)
	{
		float xloc = FMath::RandRange(-2500.0f, 2500.0f);
		float yloc = FMath::RandRange(-2500.0f, 2500.0f);
		float zloc = FMath::RandRange(0.0f, 5000.0f);
		FVector loc(xloc, yloc, zloc);
		GasClouds.Add(Cast<AGasCloud>(GetWorld()->SpawnActor(GasCloud, &loc ,&FRotator::ZeroRotator)));
	}
}

// Called every frame
void AShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(NumofShips < MaxShipCount *.2)
	{
		while(NumofShips < MaxShipCount)
		{
			SpawnShip();
		}
	}
}

void AShipSpawner::SpawnShip()
{
	float xloc = FMath::RandRange(-2000.0f, 2000.0f);
	float yloc = FMath::RandRange(-2000.0f, 2000.0f);
	float zloc = FMath::RandRange(500.0f, 4500.0f);
	FVector loc(xloc, yloc, zloc);
	ABoid* SpawnedShip = Cast<ABoid>(GetWorld()->SpawnActor(HarvestShip, &loc ,&FRotator::ZeroRotator));
	SpawnedShip->Spawner = this;
	SetShipVariables(SpawnedShip);
	NumofShips++;
}

void AShipSpawner::SetShipVariables(ABoid* Ship)
{
	
}
