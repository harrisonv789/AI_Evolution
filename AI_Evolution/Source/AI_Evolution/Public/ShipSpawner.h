/**
 * FIT3094 ASSIGNMENT 2 - GOAL PLANNING
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "GasCloud.h"
#include "GameFramework/Actor.h"
#include "ShipSpawner.generated.h"

UCLASS()
class AI_EVOLUTION_API AShipSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Entities")
	float MaxShipCount = 300;

	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<ABoid> HarvestShip;

	UPROPERTY(EditAnywhere, Category = "Entities")
	TSubclassOf<AGasCloud> GasCloud;

	int NumOfShips = 0;
	TArray<AGasCloud*> GasClouds;

	void SpawnShip();
	void SetShipVariables(ABoid* Ship);
};
