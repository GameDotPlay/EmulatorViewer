/*****************************************************************//**
 * @file   EmulatorFPCharacter.h
 * @brief  Class file for AEmulatorFPCharacter.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EmulatorFPCharacter.generated.h"

class UInputComponent;

/** This class represents a first person playable character. */
UCLASS()
class EMULATORVIEWER_API AEmulatorFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/**
	 * The default constructor.
	 */
	AEmulatorFPCharacter();

	/**
	 * Binds player input to actions.
	 * @param PlayerInputComponent The PlayerInputComponent to bind inputs to.
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	/**
	 * UnrealEngine BeginPlay() method. Gets called after all initialization and before the first Tick().
	 */
	virtual void BeginPlay() override;

private:

	/** The default walk speed. */
	float OriginalWalkSpeed;

	/** The camera component for this player. */
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	/**
	 * Move the player in the direction of the Actor forward vector.
	 * @param Value The value to move.
	 */
	void MoveForward(float Value);

	/**
	 * Move the player in the direction of the Actor right vector.
	 * @param Value The value to move.
	 */
	void StrafeRight(float Value);

	/**
	 * Add pitch rotation to the camera.
	 * @param Value
	 */
	void AddPitch(float Value);

	/**
	 * Doubles the MaxWalkSpeed.
	 */
	void DoubleSpeed();

	/**
	 * Resets walk speed back to OriginalWalkSpeed.
	 */
	void ResetNormalSpeed();
};
