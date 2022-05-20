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


// Additional force for harvesting ships
FVector APirateBoid::AdditionalForce()
{
	// Determine any nearby ships from the sensor
	TArray<AActor*> NearbyHarvesters;
	PerceptionSensor->GetOverlappingActors(NearbyHarvesters, AHarvesterBoid::StaticClass());

	// Subtract from the force direction (so that it actually goes to ships)
	const FVector Force = -(AvoidShips(NearbyHarvesters).GetSafeNormal() * TargetingStrength);
	UE_LOG(LogTemp, Warning, TEXT("Vector: %s"), *Force.ToString());
	
	// Return the final force
	return Force;
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


// Calculates the new fitness value
void APirateBoid::CalculateAndStoreFitness(EDeathReason Reason)
{
	// Sets the fitness as the gold collected
	float Fitness = GoldCollected * 50.0f;
	
	// Set a multiplier based on the reason
	switch (Reason)
	{
		case NONE:
			Fitness *= 1.0f; break;
		case SHIP_COLLISION: // This should never occur
			Fitness *= 1.0f; break;
		case WALL_COLLISION:
			Fitness *= 0.25f; break;
		case PIRATE: // This is the same as colliding with another BOID
			Fitness *= 0.25f; break;
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
	if (CurrentWaitTime > 0.0)
		CurrentWaitTime -= DeltaTime;
}


// Replaces the DNA with a new one from the population
void APirateBoid::ReplaceDNA(bool RetrieveNew)
{
	// Replace all the default values
	Super::ReplaceDNA(RetrieveNew);

	// Reset the pause time
	CurrentWaitTime = 0.0;

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
				Harvester->GoldCollected = 0.0;

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
		100.0f,			// Velocity Alignment
		100.0f,			// Separation
		10.0f,			// Centering
		1000.0f,		// Avoidance
		200.0f,			// Gas Cloud
		1000.0f,		// Tracking
	});

	// Call the base function
	Super::SetDefaultGenes();
}

