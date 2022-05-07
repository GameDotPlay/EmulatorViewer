


#include "EmulatorPlayerController.h"
#include "EmulatorFPCharacter.h"
#include "EmulatorGodPawn.h"

void AEmulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->InputComponent->BindAction("KeyboardC", IE_Pressed, this, &AEmulatorPlayerController::ChangeControlMode);
}

void AEmulatorPlayerController::ChangeControlMode()
{
	switch (this->CurrentControlMode)
	{
	case ControlMode::FirstPerson:

		this->CurrentControlMode = ControlMode::GodMode;
		this->SetupGodMode();
		break;

	case ControlMode::GodMode:

		this->CurrentControlMode = ControlMode::FirstPerson;
		this->SetupFirstPersonMode();
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("PlayerController: CurrentControlMode unknown."));
		this->SetupGodMode();
	}
}

void AEmulatorPlayerController::SetupGodMode()
{

}

void AEmulatorPlayerController::SetupFirstPersonMode()
{

}