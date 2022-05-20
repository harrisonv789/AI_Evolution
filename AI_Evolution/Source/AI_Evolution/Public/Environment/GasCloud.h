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
 * within the cloud. Clouds that are interacted with BOIDs may be able
 * to transfer gold to the BOIDs for collection.
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
	 * @brief Called when the actor first starts playing. This should
	 * start the Niagara particle effects.
	 */
	virtual void BeginPlay() override;

	
	/*************************************************************/
	public:
	
	/**
	 * @brief Default constructor initialises the default values. This
	 * will also create any necessary physics components and particle
	 * effects that may be run to create a nice feel of the cloud.
	 */
	AGasCloud();

	/**
	 * @brief Called every time the game updates. This will check to see
	 * if the gas cloud has run out of gold. If so, it will move the gas
	 * cloud to a new location somewhere in the map.
	 * @param DeltaTime [s] The time-step from the tick.
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
