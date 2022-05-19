/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

#include "ShipDataContainer.generated.h"

/**
 * @brief This data structure is filled by a ship with a series of parameters
 * about the ship's life. This includes the Gold collected, Fitness and Strength
 * values from the DNA. This allows the UI to visualise information about certain
 * ship's lives.
 */
USTRUCT(BlueprintType)
struct FShipDataContainer
{
	GENERATED_BODY()

	// A flag for if the previous generation is set
	UPROPERTY(BlueprintReadOnly)
	bool IsValid;

	// The total fitness of the current ship at the end of it's
	// life or when it was called
	UPROPERTY(BlueprintReadOnly)
	float Fitness;

	// The amount of gold stored by the ship over its life
	UPROPERTY(BlueprintReadOnly)
	float Gold;
	
	// The time the ship stayed alive for
	UPROPERTY(BlueprintReadOnly)
	float TimeAlive;

	// The property of the alignment strength from the gene
	UPROPERTY(BlueprintReadOnly)
	float StrengthAlignment;

	// The property of the separation strength from the gene
	UPROPERTY(BlueprintReadOnly)
	float StrengthSeparation;

	// The property of the centering strength from the gene
	UPROPERTY(BlueprintReadOnly)
	float StrengthCentering;

	// The property of the avoidance strength from the gene
	UPROPERTY(BlueprintReadOnly)
	float StrengthAvoidance;

	// The property of the gas cloud strength from the gene
	UPROPERTY(BlueprintReadOnly)
	float StrengthGasCloud;

	// The property of the speed strength from the gene
	UPROPERTY(BlueprintReadOnly)
	float StrengthSpeed;
};
