// Fill out your copyright notice in the Description page of Project Settings.

#include "GasCloud.h"

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
	if (GasCloudParticle->IsValid())
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(GasCloudParticle, CloudHitBox,TEXT("Hitbox Component"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}
}

// Called every frame
void AGasCloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GoldStorage <= 0)
	{
		float xloc = FMath::RandRange(-2500.0f, 2500.0f);
		float yloc = FMath::RandRange(-2500.0f, 2500.0f);
		float zloc = FMath::RandRange(0.0f, 5000.0f);
		FVector loc(xloc, yloc, zloc);
		SetActorLocation(loc);
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

