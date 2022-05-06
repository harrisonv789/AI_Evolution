/**
 * FIT3094 ASSIGNMENT 2 - GOAL PLANNING
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GasCloud.generated.h"

UCLASS()
class AI_EVOLUTION_API AGasCloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGasCloud();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* GasCloudParticle;
	
	float GoldStorage = 1000;

	UPROPERTY(EditAnywhere) USphereComponent* CloudHitBox;

	//UPROPERTY(EditAnywhere) 
	
	UFUNCTION(BlueprintCallable) float RemoveGold();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
