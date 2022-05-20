/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "HarvesterBoid.generated.h"

/**
 * @brief The harvester BOID is a special type of BOID that
 * tracks the gas clouds in the world and aims to target those
 * clouds. If the clouds are entered, then they will attempt
 * to collect Gold from the cloud. The fitness function of this
 * BOID is calculated so that ships which collect the greatest
 * amount of gold, will receive larger fitness functions, along
 * with the ability to stay alive for long periods of time.
 */
UCLASS(BlueprintType, Blueprintable)
class AI_EVOLUTION_API AHarvesterBoid : public ABoid
{
	GENERATED_BODY()
	
	/*************************************************************/
	protected:

	// The cloud that the ship is correctly collided with. This will
	//		be used for gold collection.
	UPROPERTY()
	AGasCloud* CollisionCloud;

	// The additional speed strength to add to maximum speed.
	float SpeedStrength = 1.0f;


	/*************************************************************/
	public:
	
	// The factor to apply for the time alive on the fitness function.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FitnessTimeWeighting = 0.5f;

	// The factor to apply for the gold on the fitness function.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FitnessGoldWeighting = 5.0f;


	/*************************************************************/
	protected:
	
	/**
	 * @brief Called when the game first starts playing. This will execute
	 * the base BOID class BeginPlay method first and will only additionally
	 * connect up the exit function, for when the clouds are exited from the
	 * collision.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Rather than having a fixed speed, this BOID has a speed strength
	 * value that allows it to potentially travel faster than the maximum speed.
	 * This is adjusted and can be changed in the DNA.
	 * @return [u/s] The maximum speed this BOID can travel at.
	 */
	virtual float GetMaxSpeed() override;


	/*************************************************************/
	public:
	
	/**
	 * @brief Called every frame to update the actor's position. However, as
	 * the flight path is calculated in the base class function, this will
	 * only additionally check for any gold that may have been spawned in the
	 * game when a gas cloud has been overlapped.
	 * @param DeltaTime [s] The time-step in of the tick
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Replaces the current DNA with a new one from the evolved DNA.
	 * Additionally, this will replace the speed strength that exists in the
	 * harvester ship and updates its own strength values.
	 * @param RetrieveNew A flag for if retrieving a new DNA from the evolve manager.
	 */
	virtual void ReplaceDNA(bool RetrieveNew = true) override;

	/**
	 * @brief Calculates a new fitness score based on the current parameters
	 * of the ship. For this particular BOID, the fitness is dependent on how
	 * long the ship remains alive for, and for how much gold the ship collects.
	 * These factors can be tweaked to find the most optimum way for ships
	 * to evolve strengths to achieve the goal of avoiding other ships, whilst
	 * also collecting gold from the gas clouds.
	 * @param Reason The cause of the death.
	 */
	virtual void CalculateAndStoreFitness(EDeathReason Reason) override;

	/**
	 * @brief Updates the statistics struct to all of the values from the ship.
	 * This will include updating the additional speed parameter and the gold
	 * collected values.
	 */
	virtual void UpdateStatistics() override;

	/**
	 * @brief Called when the hit-box is overlapped. This will handle killing
	 * the BOID due to a collision, or potentially collecting gold if it is
	 * a gas cloud that has been overlapped.
	 * @param OverlappedComponent	The current overlapped component
	 * @param OtherActor			The actor that is overlapping
	 * @param OtherComponent		The other actor's component that is overlapping
	 * @param OtherBodyIndex		The other actor's body index overlapping
	 * @param bFromSweep			Whether or not the overlapping is caused by a sweep detection
	 * @param SweepResult			The hit result from the collision
	 */
	virtual void OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,  bool bFromSweep, const FHitResult& SweepResult) override;

	/**
	 * @brief Called when the hit-box overlapping is complete. This will
	 * signal that a gas cloud has been exited, and the cloud can no longer
	 * be used to collect gold from.
	 * @param OverlappedComponent	The current overlapped component
	 * @param OtherActor			The actor that is overlapping
	 * @param OtherComponent		The other actor's component that is overlapping
	 * @param OtherBodyIndex		The other actor's body index overlapping
	 */
	UFUNCTION()
	void OnHitBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent,  AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	/**
	 * @brief Sets the list of defaults for the Harvester BOID. This will be set
	 * based on simulated evolutionary values and will be found after trial and error
	 * of running the simulation for a long enough time such that the system correctly
	 * evolves.
	 */
	virtual void SetDefaultGenes() override;
};
