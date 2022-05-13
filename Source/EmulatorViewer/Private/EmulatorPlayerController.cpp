
#include "EmulatorPlayerController.h"
#include "UI/MainHUDWidget.h"

void AEmulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->MainHUD = Cast<UMainHUDWidget>(CreateWidget(this, this->MainHUDWidget, FName(TEXT("Main HUD Widget"))));

	if (this->MainHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("MainHUD not null."));
		this->MainHUD->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainHUD is null."));
	}

	this->SetObserveInteractionMode();
}

void AEmulatorPlayerController::ToggleControlMode()
{
	switch (this->CurrentControlMode)
	{
	case FControlMode::FirstPerson:

		this->SetGodControlMode();
		break;

	case FControlMode::GodMode:

		this->SetFirstPersonControlMode();
		break;

	default:
		this->SetGodControlMode();
	}
}

void AEmulatorPlayerController::ChangeInteractionMode(FInteractionMode NewInteractionMode)
{
	switch (NewInteractionMode)
	{
	case FInteractionMode::FullMenuMode:

		this->SetFullMenuInteractionMode();
		break;

	case FInteractionMode::PopupMenuMode:

		this->SetPopupMenuInteractionMode();
		break;

	case FInteractionMode::ObserveMode:

		this->SetObserveInteractionMode();
		break;

	case FInteractionMode::InteractMode:

		this->SetInteractInteractionMode();
		break;

	case FInteractionMode::BuildMode:

		this->SetBuildInteractionMode();
		break;

	default:

		UE_LOG(LogTemp, Error, TEXT("PlayerController: NewInteractionMode unknown."));
		break;
	}
}

void AEmulatorPlayerController::SetFullMenuInteractionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("In SetFullMenuInteractionMode()"));

	this->SetInputMode(FInputModeUIOnly());
	this->CurrentInteractionMode = FInteractionMode::FullMenuMode;
}

void AEmulatorPlayerController::SetPopupMenuInteractionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("In SetPopupMenuInteractionMode()"));

	this->SetInputMode(FInputModeGameAndUI());
	this->CurrentInteractionMode = FInteractionMode::PopupMenuMode;
}

void AEmulatorPlayerController::SetObserveInteractionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("In SetObserveInteractionMode()"));

	this->SetInputMode(FInputModeGameAndUI());
	this->MainHUD->SetInteractionModeText(FText::FromString(TEXT("Observe Mode")));
	this->CurrentInteractionMode = FInteractionMode::ObserveMode;
}

void AEmulatorPlayerController::SetInteractInteractionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("In SetInteractInteractionMode()"));

	this->SetMouseCursorWidget(EMouseCursor::GrabHand, nullptr);
	this->SetInputMode(FInputModeGameAndUI());
	this->MainHUD->SetInteractionModeText(FText::FromString(TEXT("Interact Mode")));
	this->CurrentInteractionMode = FInteractionMode::InteractMode;
}

void AEmulatorPlayerController::SetBuildInteractionMode()
{
	UE_LOG(LogTemp, Warning, TEXT("In SetBuildInteractionMode()"));

	this->SetInputMode(FInputModeGameAndUI());
	this->MainHUD->SetInteractionModeText(FText::FromString(TEXT("Build Mode")));
	this->CurrentInteractionMode = FInteractionMode::BuildMode;
}

void AEmulatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	this->InputComponent->BindAction("Keyboard1", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::SetObserveInteractionMode);
	this->InputComponent->BindAction("Keyboard2", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::SetInteractInteractionMode);
	this->InputComponent->BindAction("Keyboard3", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::SetBuildInteractionMode);
}

void AEmulatorPlayerController::SetGodControlMode()
{
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true;
	this->bEnableMouseOverEvents = true;
	this->bEnableTouchEvents = true;

	this->CurrentControlMode = FControlMode::GodMode;
}

void AEmulatorPlayerController::SetFirstPersonControlMode()
{
	this->bShowMouseCursor = false;
	this->bEnableClickEvents = false;
	this->bEnableMouseOverEvents = false;
	this->bEnableTouchEvents = false;
	
	this->CurrentControlMode = FControlMode::FirstPerson;
}