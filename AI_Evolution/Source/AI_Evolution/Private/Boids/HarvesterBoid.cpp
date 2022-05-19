/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Boids/HarvesterBoid.h"


// Sets default values
AHarvesterBoid::AHarvesterBoid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHarvesterBoid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHarvesterBoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

