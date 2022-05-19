/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GasCloud.generated.h"

/**
 * @brief The class that handles the cloud of gas that stores some gold
 * within the cloud.
 */
UCLASS()
class AI_EVOLUTION_API AGasCloud : public AActor
{
	GENERATED_BODY()

	/*************************************************************/
	public:	

	// The current cloud particle system that is shown
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* GasCloudParticle;

	// The current storage of the gold
	float GoldStorage = 1000;

	// The hit-box of the cloud
	UPROPERTY(EditAnywhere)
	USphereComponent* CloudHitBox;

	
	/*************************************************************/
	protected:
	
	/**
	 * @brief Called when the actor first starts playing
	 */
	virtual void BeginPlay() override;

	
	/*************************************************************/
	public:
	
	/**
	 * @brief Default constructor initialises the default values
	 */
	AGasCloud();

	/**
	 * @brief Called every time the game updates
	 * @param DeltaTime The time-step in seconds
	 */
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief Removes gold from the cloud and returns the current gold value.
	 * This is executed by a Boid that attempts to collect the gold.
	 * @return The value of the gold collected by the ship.
	 */
	UFUNCTION(BlueprintCallable)
	float RemoveGold();
	
};
