


#include "EmulatorPlayerController.h"
#include "EmulatorFPCharacter.h"
#include "EmulatorGodPawn.h"

void AEmulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->InputComponent->BindAction("KeyboardC", IE_Pressed, this, &AEmulatorPlayerController::ToggleControlMode);
}

void AEmulatorPlayerController::ToggleControlMode()
{
	switch (this->CurrentControlMode)
	{
	case ControlMode::FirstPerson:

		this->CurrentControlMode = ControlMode::GodMode;
		this->TransitionToGodMode();
		break;

	case ControlMode::GodMode:

		this->CurrentControlMode = ControlMode::FirstPerson;
		this->TransitionToFirstPersonMode();
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("PlayerController: CurrentControlMode unknown."));
		this->TransitionToGodMode();
	}
}

void AEmulatorPlayerController::ChangeInteractionMode()
{

}

void AEmulatorPlayerController::TransitionToGodMode()
{

}

void AEmulatorPlayerController::TransitionToFirstPersonMode()
{

}