/**
 * FIT3094 ASSIGNMENT 3 - EVOLUTION
 * Author: Harrison Verrios
 */

#pragma once

/**
 * @brief Defines the reason that a Ship died. This will
 * be used for the fitness calculation, depending on
 * the exact reason.
 */
UENUM(Blueprintable, BlueprintType)
enum EDeathReason
{
	// No death
    NONE				= 0,

	// A collision with another ship
	SHIP_COLLISION		= 1,

	// A collision with a wall
	WALL_COLLISION		= 2,

	// Pirate has taken the ship
	PIRATE				= 3,
};
