/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Boids/PirateBoid.h"
#include "Boids/HarvesterBoid.h"


// Sets default values
APirateBoid::APirateBoid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Returns thew ship filtering
TSubclassOf<AActor> APirateBoid::GetShipFilter()
{
	return TSubclassOf<APirateBoid>();
}


// Gets the minimum speed of the BOID
float APirateBoid::GetMinSpeed()
{
	// If waiting, do not move
	return CurrentWaitTime <= 0.0 ? 550 : 0.0;
}


// Gets the maximum speed of the BOID
float APirateBoid::GetMaxSpeed()
{
	// Make sure the two speed's match
	return GetMinSpeed();
}


// Called every frame
void APirateBoid::Tick(float DeltaTime)
{
	// Call the base tick function
	Super::Tick(DeltaTime);

	// Decrease the wait time if waiting
	if (CurrentWaitTime > 0.0)
		CurrentWaitTime -= DeltaTime;
}


// On collided with another trigger
void APirateBoid::OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Calls the base function for collision with walls
	Super::OnHitBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);

	// If colliding with another actor
	if (OtherComponent->GetName().Equals(TEXT("Boid Collision Component")))
	{
		// Check for another ship
		ABoid* Ship = Cast<ABoid>(OtherActor);
		if (Ship != nullptr && Invincibility <= 0)
		{
			// Check for a pirate ship
			if (OtherActor->IsA(StaticClass()))
			{
				// Call the death function for pirates
				Death(PIRATE);
			}

			// Otherwise, assume it is a harvester
			else
			{
				// Call the death function on the other ship
				AHarvesterBoid* Harvester = Cast<AHarvesterBoid>(Ship);

				// Take the harvester's current gold
				GoldCollected += Harvester->GoldCollected;
				Harvester->GoldCollected = 0.0;

				// Reset the wait time
				CurrentWaitTime = MaxWaitTime;

				// Call the death function on the harvester
				Harvester->Death(PIRATE);
			}
		}
	}
}

