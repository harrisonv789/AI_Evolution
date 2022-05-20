/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#include "Boids/HarvesterBoid.h"

// Called when the game starts or when spawned
void AHarvesterBoid::BeginPlay()
{
	// Call the base begin play method
	Super::BeginPlay();

	// Add in functionality for exiting gas clouds
	BoidCollision->OnComponentEndOverlap.AddDynamic(this, &AHarvesterBoid::OnHitBoxOverlapEnd);
}


// Calculates the maximum speed of the BOID
float AHarvesterBoid::GetMaxSpeed()
{
	// Returns a calculation based on the speed strength gene
	return MaxSpeed + SpeedStrength / 5.0;
}


// Called every frame
void AHarvesterBoid::Tick(float DeltaTime)
{
	// Call the base tick method
	Super::Tick(DeltaTime);

	// Check for gas cloud gold harvesting
	if (CollisionCloud != nullptr)
		GoldCollected += CollisionCloud->RemoveGold();
}


// Replaces the DNA with a new one from the population
void AHarvesterBoid::ReplaceDNA(bool RetrieveNew)
{
	// Replace all the default values
	Super::ReplaceDNA(RetrieveNew);

	// Also replace the speed strength
	SpeedStrength = ShipDNA.StrengthValues[5];
}


// Calculates the new fitness value
void AHarvesterBoid::CalculateAndStoreFitness(EDeathReason Reason)
{
	// Calculate the Time fitness factor (with a square that benefits those alive)
	const float TimeValue = CurrentAliveTime;
		
	// Calculate the fitness using the weightings
	float Fitness = (TimeValue * FitnessTimeWeighting) + (GoldCollected * FitnessGoldWeighting);

	// Set a multiplier based on the reason
	switch (Reason)
	{
	case NONE:
		Fitness *= 1.0f; break;
	case SHIP_COLLISION:
		Fitness *= 0.25f; break;
	case WALL_COLLISION:
		Fitness *= 0.25f; break;
	case PIRATE:
		Fitness *= 0.50f; break;
	}

	// Update the stored fitness on the DNA
	ShipDNA.StoredFitness = Fitness;
	
	// Calls the base function which will update the statistics
	Super::CalculateAndStoreFitness(Reason);
}


// Updates the statistic information struct
void AHarvesterBoid::UpdateStatistics()
{
	// Update the speed strength
	ShipStatistics.StrengthSpeed = SpeedStrength;

	// Update the base statistic information
	// This is called after as the fitness is calculated
	Super::UpdateStatistics();
}


// On collided with another trigger
void AHarvesterBoid::OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Call the base event function call
	Super::OnHitBoxOverlapBegin(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);

	// If colliding with another actor
	if (OtherComponent->GetName().Equals(TEXT("Boid Collision Component")))
	{
		// Check for a ship
		ABoid* Ship = Cast<ABoid>(OtherActor);
		if (Ship != nullptr && Invincibility <= 0)
		{
			// Check for a harvester ship
			if (OtherActor->IsA(StaticClass()))
			{
				// Call the death function for pirates
				Death(SHIP_COLLISION);

				// Avoid any other functionality in this function
				return;
			}

			// Pirate collisions are handled by the pirate
		}
	}

	// Attempt to get the cloud from the collision
	AGasCloud* Cloud = Cast<AGasCloud>(OtherActor);
	if (Cloud != nullptr)
	{
		CollisionCloud = Cloud;
	}
}


// Called when the gas cloud overlaps the current actor
void AHarvesterBoid::OnHitBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	AGasCloud* cloud = Cast<AGasCloud>(OtherActor);
	if (cloud != nullptr)
		CollisionCloud = nullptr;
}


// Gets the list of defaults
void AHarvesterBoid::SetDefaultGenes()
{
	ShipDNA.SetDefault({
		369.0f,			// Velocity Alignment
		161.0f,			// Separation
		0.8f,			// Centering
		1042.0f,		// Avoidance
		68.0f,			// Gas Cloud
		885.0f,			// Speed
	});

	// Call the base function
	Super::SetDefaultGenes();
}

