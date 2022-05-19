// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "HarvesterBoid.generated.h"

UCLASS()
class AI_EVOLUTION_API AHarvesterBoid : public ABoid
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHarvesterBoid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
