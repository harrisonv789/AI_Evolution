/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Boids/PirateBoid.h"


// Sets default values
APirateBoid::APirateBoid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APirateBoid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APirateBoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

