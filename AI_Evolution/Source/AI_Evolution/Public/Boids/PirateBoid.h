/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "PirateBoid.generated.h"

/**
 * @brief This is the class for handling the pirate ship.
 * The pirate ship is a type of BOID that is able to attempt
 * to find and collide with ships, taking their gold.
 */
UCLASS(Blueprintable, BlueprintType)
class AI_EVOLUTION_API APirateBoid : public ABoid
{
	GENERATED_BODY()

	/*************************************************************/
	protected:
	
	/**
	 * @brief Called when the simulation first starts running
	 */
	virtual void BeginPlay() override;


	/*************************************************************/
	public:
	
	/**
	 * @brief The base constructor for the BOID object
	 */
	APirateBoid();

	/**
	 * @brief Called every frame to update the BOID's position
	 * @param DeltaTime [s] The time-step between frames
	 */
	virtual void Tick(float DeltaTime) override;

};
