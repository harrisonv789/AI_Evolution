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

	// The maximum wait time after plundering a ship
	UPROPERTY(BlueprintReadOnly)
	float MaxWaitTime = 5.0;

	// The current time waiting after plundering a ship
	UPROPERTY(BlueprintReadOnly)
	float CurrentWaitTime = 0.0;
	

	/*************************************************************/

	/**
	 * @brief This method returns the class that the flocking mechanism
	 * should be looking for. For Pirates, this should only be the Pirate
	 * ship type, as it should not be velocity matching with other BOID types.
	 * @return The current filtering of the ships.
	 */
	virtual TSubclassOf<AActor> GetShipFilter() override;

	/**
	 * @brief This method returns the minimum speed that a BOID can
	 * move at. This is constant for the ships, and is set to a speed
	 * of 550 units per second. However, if the ship has just plundered
	 * a harvester, then it will change the speed to be zero so that it
	 * does not move.
	 * @return [u/s] The minimum speed that a BOID can move at.
	 */
	virtual float GetMinSpeed() override;

	/**
	 * @brief This method returns the maximum speed that a BOID
	 * can move at. This is constant for the ships, and is set to
	 * a speed of 550 units per second. However, if the ship has just
	 * plundered a harvester, then it will change the speed to be zero
	 * so that it does not move.
	 * @return [u/s] The maximum speed that a BOID can move at.
	 */
	virtual float GetMaxSpeed () override;


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

	/**
	 * @brief Called when the hit-box is overlapped. This will handle any
	 * additional code that checks to see if the other actor is a Pirate ship.
	 * Pirate ships cannot die if they hit a harvester ship.
	 * @param OverlappedComponent	The current overlapped component
	 * @param OtherActor			The actor that is overlapping
	 * @param OtherComponent		The other actor's component that is overlapping
	 * @param OtherBodyIndex		The other actor's body index overlapping
	 * @param bFromSweep			Whether or not the overlapping is caused by a sweep detection
	 * @param SweepResult			The hit result from the collision
	 */
	virtual void OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
