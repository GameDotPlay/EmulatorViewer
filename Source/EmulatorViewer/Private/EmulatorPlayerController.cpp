
#include "EmulatorPlayerController.h"
#include "UI/MainHUDWidget.h"
#include "EmulatorGodPawn.h"
#include "InteractableHighlighting.h"
#include "Kismet/GameplayStatics.h"

void AEmulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->CurrentPawn = Cast<AEmulatorGodPawn>(this->GetPawn());
	check(this->CurrentPawn);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Floor")), Actors);
	check(Actors.Num() > 0);
	this->FloorZ = Actors[0]->GetActorLocation().Z;

	this->MainHUD = Cast<UMainHUDWidget>(CreateWidget(this, this->MainHUDWidget, FName(TEXT("Main HUD Widget"))));
	check(this->MainHUD);

	//this->MainHUD->AddToViewport();

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
	this->SetInputMode(FInputModeUIOnly());
	this->CurrentInteractionMode = FInteractionMode::FullMenuMode;
}

void AEmulatorPlayerController::SetPopupMenuInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->CurrentInteractionMode = FInteractionMode::PopupMenuMode;
}

void AEmulatorPlayerController::SetObserveInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->MainHUD->SetInteractionModeText(FText::FromString(TEXT("Observe Mode")));
	this->CurrentInteractionMode = FInteractionMode::ObserveMode;
}

void AEmulatorPlayerController::SetInteractInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->MainHUD->SetInteractionModeText(FText::FromString(TEXT("Interact Mode")));
	this->CurrentInteractionMode = FInteractionMode::InteractMode;
}

void AEmulatorPlayerController::SetBuildInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->MainHUD->SetInteractionModeText(FText::FromString(TEXT("Build Mode")));
	this->CurrentInteractionMode = FInteractionMode::BuildMode;
}

FInputModeGameAndUI AEmulatorPlayerController::GetDefaultInputMode()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

	return InputMode;
}

void AEmulatorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	this->InputComponent->BindAction("Keyboard1", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleKeyboard1);
	this->InputComponent->BindAction("Keyboard2", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleKeyboard2);
	this->InputComponent->BindAction("Keyboard3", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleKeyboard3);
	this->InputComponent->BindAction("KeyboardF", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleKeyboardF);
	this->InputComponent->BindAction("KeyboardEND", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleKeyboardEND);

	this->InputComponent->BindAction("MiddleMouseButton", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleMiddleMouseButtonPressed);
	this->InputComponent->BindAction("MiddleMouseButton", EInputEvent::IE_Released, this, &AEmulatorPlayerController::HandleMiddleMouseButtonReleased);
	this->InputComponent->BindAction("LeftMouseButton", EInputEvent::IE_Released, this, &AEmulatorPlayerController::HandleLeftMouseButton);
	this->InputComponent->BindAction("RightMouseButton", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleRightMouseButton);

	this->InputComponent->BindAxis("MouseWheel", this, &AEmulatorPlayerController::HandleMouseWheel);
	this->InputComponent->BindAxis("MouseX", this, &AEmulatorPlayerController::HandleMouseXAxis);
	this->InputComponent->BindAxis("MouseY", this, &AEmulatorPlayerController::HandleMouseYAxis);
	this->InputComponent->BindAxis("ForwardAxis", this, &AEmulatorPlayerController::HandleForwardAxis);
	this->InputComponent->BindAxis("RightAxis", this, &AEmulatorPlayerController::HandleRightAxis);
}

void AEmulatorPlayerController::LeftClickSelect()
{
	FHitResult HitResult;
	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	if (HitActor)
	{
		if (this->CurrentSelection == HitActor)
		{
			return;
		}

		if (this->CurrentSelection != nullptr)
		{
			// Turn off current selection highlighting.
			UInteractableHighlighting* HighlightComponent = this->GetInteractableComponent(this->CurrentSelection);
			if (HighlightComponent)
			{
				HighlightComponent->SetSelectedDisabled();
			}
		}
		
		UInteractableHighlighting* HighlightComponent = this->GetInteractableComponent(HitActor);
		if (HighlightComponent)
		{
			HighlightComponent->SetSelectedActive();
			this->CurrentSelection = HitActor;
			FVector HitActorExtents;
			FVector HitActorOrigin;
			HitActor->GetActorBounds(true, HitActorOrigin, HitActorExtents, true);
			DrawDebugString(GetWorld(), HitActorOrigin + FVector(0, 0, 100), FString(*HitActor->GetActorNameOrLabel()), nullptr, FColor::Yellow, 1.f, true, 2.f);
		}
	}
}

UInteractableHighlighting* AEmulatorPlayerController::GetInteractableComponent(AActor* Actor)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}

	UActorComponent* Component = Actor->GetComponentByClass(UInteractableHighlighting::StaticClass());
	UInteractableHighlighting* HighlightComponent = Cast<UInteractableHighlighting>(Component);

	if (HighlightComponent == nullptr)
	{
		return nullptr;
	}
	else
	{
		return HighlightComponent;
	}
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

void AEmulatorPlayerController::HandleKeyboard1()
{
	this->SetObserveInteractionMode();
}

void AEmulatorPlayerController::HandleKeyboard2()
{
	this->SetInteractInteractionMode();
}

void AEmulatorPlayerController::HandleKeyboard3()
{
	this->SetBuildInteractionMode();
}

void AEmulatorPlayerController::HandleKeyboardF()
{
	if (this->CurrentSelection != nullptr)
	{
		FVector SelectionExtents;
		FVector SelectionOrigin;
		this->CurrentSelection->GetActorBounds(true, SelectionOrigin, SelectionExtents, true);
		this->CurrentPawn->KeyboardF(SelectionOrigin);
	}
}

void AEmulatorPlayerController::HandleKeyboardEND()
{
	this->CurrentPawn->KeyboardEND(this->FloorZ + FloorZOffset);
}

void AEmulatorPlayerController::HandleMiddleMouseButtonPressed()
{
	this->CurrentPawn->MiddleMousePressed();
}

void AEmulatorPlayerController::HandleMiddleMouseButtonReleased()
{
	this->CurrentPawn->MiddleMouseReleased();
}

void AEmulatorPlayerController::HandleLeftMouseButton()
{
	this->LeftClickSelect();
}

void AEmulatorPlayerController::HandleRightMouseButton()
{

}

void AEmulatorPlayerController::HandleMouseWheel(float Value)
{
	this->CurrentPawn->MouseWheelAxis(Value);
}

void AEmulatorPlayerController::HandleMouseXAxis(float Value)
{
	this->CurrentPawn->MouseXAxis(Value);
}

void AEmulatorPlayerController::HandleMouseYAxis(float Value)
{
	this->CurrentPawn->MouseYAxis(Value);
}

void AEmulatorPlayerController::HandleForwardAxis(float Value)
{
	this->CurrentPawn->MoveForward(Value);
}

void AEmulatorPlayerController::HandleRightAxis(float Value)
{
	this->CurrentPawn->MoveRight(Value);
}