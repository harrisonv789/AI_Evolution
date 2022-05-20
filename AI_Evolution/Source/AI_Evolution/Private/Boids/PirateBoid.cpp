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

	// Ensure the statistics for pirates are set.
	ShipStatistics.IsPirate = true;
}


// Returns thew ship filtering
TSubclassOf<AActor> APirateBoid::GetShipFilter()
{
	return TSubclassOf<APirateBoid>();
}


// Additional force for harvesting ships
FVector APirateBoid::AdditionalForce()
{
	// Determine any nearby ships from the sensor
	TArray<AActor*> NearbyHarvesters;
	PerceptionSensor->GetOverlappingActors(NearbyHarvesters, AHarvesterBoid::StaticClass());

	// Subtract from the force direction (so that it actually goes to ships)
	const FVector Force = -(AvoidShips(NearbyHarvesters).GetSafeNormal() * TargetingStrength);
	
	// Return the final force
	return Force;
}


// Gets the minimum speed of the BOID
float APirateBoid::GetMinSpeed()
{
	// If waiting, do not move
	return CurrentWaitTime <= 0.0f ? 550.0f : 0.0f;
}


// Gets the maximum speed of the BOID
float APirateBoid::GetMaxSpeed()
{
	// Make sure the two speed's match
	return GetMinSpeed();
}


// Calculates the new fitness value
void APirateBoid::CalculateAndStoreFitness(EDeathReason Reason)
{
	// Sets the fitness as the gold collected
	float Fitness = GoldCollected * 50.0f + (static_cast<float>(HarvestersPlundered) * 5.0);
	
	// Set a multiplier based on the reason
	switch (Reason)
	{
		case NONE:
			Fitness *= 1.0f; break;
		case SHIP_COLLISION: // This should never occur
			Fitness *= 1.0f; break;
		case WALL_COLLISION:
			Fitness *= 0.75f; break;
		case PIRATE: // This is the same as colliding with another BOID
			Fitness *= 0.75f; break;
	}
	
	// Update the DNA fitness
	ShipDNA.StoredFitness = Fitness;
	
	// Calls the base function
	Super::CalculateAndStoreFitness(Reason);
}


// Updates the statistic information struct
void APirateBoid::UpdateStatistics()
{
	// Ensure it sets this as a pirate
	ShipStatistics.IsPirate = true;

	// Update the targeting value
	ShipStatistics.StrengthSpeed = TargetingStrength;

	// Update the base statistic information
	// This is called after as the fitness is calculated
	Super::UpdateStatistics();
}


// Called every frame
void APirateBoid::Tick(float DeltaTime)
{
	// Call the base tick function
	Super::Tick(DeltaTime);

	// Decrease the wait time if waiting
	if (CurrentWaitTime > 0.0f)
		CurrentWaitTime -= DeltaTime;
}


// Replaces the DNA with a new one from the population
void APirateBoid::ReplaceDNA(bool RetrieveNew)
{
	// Replace all the default values
	Super::ReplaceDNA(RetrieveNew);

	// Reset the pause time
	CurrentWaitTime = 0.0f;

	// Reset the plunder count
	HarvestersPlundered = 0;

	// Also replace the targeting strength
	TargetingStrength = ShipDNA.StrengthValues[5];
}


// Sets the DNA to something else
void APirateBoid::SetDNA(DNA Other)
{
	ShipDNA = Other;
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
			if (Ship->IsA(StaticClass()))
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
				Harvester->GoldCollected = 0.0f;

				// Reset the wait time
				CurrentWaitTime = MaxWaitTime;

				// Call the death function on the harvester
				Harvester->Death(PIRATE);
			}
		}
	}
}


// Gets the list of defaults
void APirateBoid::SetDefaultGenes()
{
	ShipDNA.SetDefault( {
		92.0f,			// Velocity Alignment
		116.0f,			// Separation
		9.0f,			// Centering
		1018.0f,			// Avoidance
		173.0f,			// Gas Cloud
		892.0f,			// Tracking
	});

	// Call the base function
	Super::SetDefaultGenes();
}

