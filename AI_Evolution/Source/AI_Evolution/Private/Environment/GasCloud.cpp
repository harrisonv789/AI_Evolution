/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Environment/GasCloud.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

// Sets default values
AGasCloud::AGasCloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CloudHitBox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox Component"));
	CloudHitBox->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AGasCloud::BeginPlay()
{
	Super::BeginPlay();

	// If the particle system exists
	if (GasCloudParticle->IsValid())
	{
		// Spawn the particles
		UNiagaraFunctionLibrary::SpawnSystemAttached(GasCloudParticle, CloudHitBox,
			TEXT("Hitbox Component"), FVector::ZeroVector, FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset, true);
	}
}


// Called every frame
void AGasCloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If no gold is remaining
	if(GoldStorage <= 0)
	{
		const float XLoc = FMath::RandRange(-2500.0f, 2500.0f);
		const float YLoc = FMath::RandRange(-2500.0f, 2500.0f);
		const float ZLoc = FMath::RandRange(0.0f, 5000.0f);
		const FVector Location (XLoc, YLoc, ZLoc);

		// Update the location
		SetActorLocation(Location);

		// Reset the gold count
		GoldStorage = 1000;
	}
}


float AGasCloud::RemoveGold()
{
	if(GoldStorage > 0)
	{
		GoldStorage--;
		return 0.01;
	}
	
	return 0;
}

