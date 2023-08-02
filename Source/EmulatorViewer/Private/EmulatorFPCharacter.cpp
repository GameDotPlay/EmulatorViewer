/*****************************************************************//**
 * @file   EmulatorFPCharacter.cpp
 * @brief  Implementation file for EmulatorFPCharacter.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#include "EmulatorFPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

/**
 * The default constructor.
 * Initializes any default values and sets transform hierarchy.
 */
AEmulatorFPCharacter::AEmulatorFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(RootComponent);
}

/**
 * UnrealEngine BeginPlay() method. Gets called after all initialization and before the first Tick().
 */
void AEmulatorFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	this-> OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

/**
* Binds player input to actions.
* @param PlayerInputComponent The PlayerInputComponent to bind inputs to.
*/
void AEmulatorFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardAxis", this, &AEmulatorFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis", this, &AEmulatorFPCharacter::StrafeRight);

	PlayerInputComponent->BindAxis("MouseX", this, &AEmulatorFPCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &AEmulatorFPCharacter::AddPitch);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &AEmulatorFPCharacter::DoubleSpeed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &AEmulatorFPCharacter::ResetNormalSpeed);
}

/**
 * Adds movement input in the Actor forward vector direction.
 * @param Value The value to add.
 */
void AEmulatorFPCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

/**
 * Adds movement input in the Actor right vector direction.
 * @param Value The value to add.
 */
void AEmulatorFPCharacter::StrafeRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

/**
 * Adds controller pitch input.
 * @param Value The value to add.
 */
void AEmulatorFPCharacter::AddPitch(float Value)
{
	// Inverted Y axis hard coded.
	AddControllerPitchInput(-Value);
}

/**
 * Doubles the MaxWalkSpeed of the CharacterMovementComponent.
 */
void AEmulatorFPCharacter::DoubleSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed *= 2;
}

/**
 * Resets the MaxWalkSpeed of the CharacterMovementComponent back to OriginalWalkSpeed.
 */
void AEmulatorFPCharacter::ResetNormalSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = this->OriginalWalkSpeed;
}
