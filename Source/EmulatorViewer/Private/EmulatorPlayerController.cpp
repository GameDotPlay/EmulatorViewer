


#include "EmulatorPlayerController.h"
#include "EmulatorFPCharacter.h"
#include "EmulatorGodPawn.h"

void AEmulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AEmulatorPlayerController::ToggleControlMode()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerController: KeyboardC registered."));

	switch (this->CurrentControlMode)
	{
	case FControlMode::FirstPerson:

		UE_LOG(LogTemp, Warning, TEXT("PlayerController: case FControlMode::FirstPerson entered."));
		this->SetGodControlMode();
		break;

	case FControlMode::GodMode:

		UE_LOG(LogTemp, Warning, TEXT("PlayerController: case FControlMode::GodMode entered."));
		this->SetFirstPersonControlMode();
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("PlayerController: CurrentControlMode unknown."));
		this->SetGodControlMode();
	}
}

void AEmulatorPlayerController::ChangeInteractionMode(FInteractionMode NewInteractionMode)
{
	switch (NewInteractionMode)
	{
	case FInteractionMode::FullMenuMode:

		this->bShowMouseCursor = true;
		this->SetInputMode(FInputModeUIOnly());
		this->CurrentInteractionMode = FInteractionMode::FullMenuMode;
		break;

	case FInteractionMode::ObserveMode:

		this->CurrentInteractionMode = FInteractionMode::ObserveMode;
		break;

	case FInteractionMode::InteractMode:

		this->CurrentInteractionMode = FInteractionMode::InteractMode;
		break;

	case FInteractionMode::BuildMode:

		this->bShowMouseCursor = true;
		this->CurrentInteractionMode = FInteractionMode::BuildMode;
		break;

	default:

		UE_LOG(LogTemp, Error, TEXT("PlayerController: NewInteractionMode unknown."));
		break;
	}
}

void AEmulatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	this->InputComponent->BindAction("KeyboardC", IE_Pressed, this, &AEmulatorPlayerController::ToggleControlMode);
}

void AEmulatorPlayerController::SetGodControlMode()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerController: SetupGodControlMode() entered."));

	APawn* GodCharacter = Cast<APawn>(this->GodModeCharacter);
	if (!GodCharacter)
	{
		return;
	}

	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true;
	this->bEnableMouseOverEvents = true;
	this->bEnableTouchEvents = true;

	GodCharacter->SetActorLocation(GetPawn()->GetActorLocation());
	this->Possess(GodCharacter);

	this->CurrentControlMode = FControlMode::GodMode;
}

void AEmulatorPlayerController::SetFirstPersonControlMode()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerController: SetFirstPersonControlMode() entered."));

	APawn* FPCharacter = Cast<APawn>(this->FirstPersonCharacter);
	if (!FPCharacter)
	{
		return;
	}

	this->bShowMouseCursor = false;
	this->bEnableClickEvents = false;
	this->bEnableMouseOverEvents = false;
	this->bEnableTouchEvents = false;
	
	FPCharacter->SetActorLocation(GetPawn()->GetActorLocation());
	this->Possess(FPCharacter);

	this->CurrentControlMode = FControlMode::FirstPerson;
}