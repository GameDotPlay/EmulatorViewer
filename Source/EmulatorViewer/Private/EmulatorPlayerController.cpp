
#include "EmulatorPlayerController.h"
#include "EmulatorGodPawn.h"
#include "InteractableHighlighting.h"
#include "Kismet/GameplayStatics.h"
#include "PopulateDetailsInterface.h"
#include "UI/DetailsPopupWidget.h"
#include "UI/EmulatorViewerHUD.h"
#include "UI/BuildModeUIWidget.h"
#include "DynamicStraightConveyor.h"
#include "Camera/CameraComponent.h"

void AEmulatorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->CurrentPawn = Cast<IPawnInterface>(this->GetPawn());
	check(this->CurrentPawn);
	
	this->MainHUD = this->GetHUD<AEmulatorViewerHUD>();
	check(this->MainHUD);

	this->MainHUD->ShowInteractionModeLabel();
	this->SetObserveInteractionMode();
}

void AEmulatorPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


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
	this->CurrentBuildModeState = FBuildModeState::NotBuilding;
	this->CurrentMouseCursor = EMouseCursor::Default;
}

void AEmulatorPlayerController::SetPopupMenuInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->CurrentInteractionMode = FInteractionMode::PopupMenuMode;
	this->CurrentBuildModeState = FBuildModeState::NotBuilding;
	this->CurrentMouseCursor = EMouseCursor::Default;
}

void AEmulatorPlayerController::SetObserveInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->MainHUD->SetInteractionModeLabel(FText::FromString(TEXT("Observe Mode")));
	this->CurrentInteractionMode = FInteractionMode::ObserveMode;
	this->CurrentBuildModeState = FBuildModeState::NotBuilding;
	this->CurrentMouseCursor = EMouseCursor::Default;
}

void AEmulatorPlayerController::SetInteractInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->MainHUD->SetInteractionModeLabel(FText::FromString(TEXT("Interact Mode")));
	this->CurrentInteractionMode = FInteractionMode::InteractMode;
	this->CurrentBuildModeState = FBuildModeState::NotBuilding;
	this->CurrentMouseCursor = EMouseCursor::GrabHand;
}

void AEmulatorPlayerController::SetBuildInteractionMode()
{
	this->SetInputMode(this->GetDefaultInputMode());
	this->MainHUD->SetInteractionModeLabel(FText::FromString(TEXT("Build Mode")));
	this->MainHUD->ShowBuildModeUI();
	this->MainHUD->GetBuildModeUI()->GetBuildObjectsMenu()->GetCreateStraightButton()->OnClicked.AddUniqueDynamic(this, &AEmulatorPlayerController::CreateStraightConveyor);
	this->CurrentInteractionMode = FInteractionMode::BuildMode;
	this->CurrentBuildModeState = FBuildModeState::NotBuilding;
	this->CurrentMouseCursor = EMouseCursor::Default;
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
	this->InputComponent->BindAction("KeyboardE", EInputEvent::IE_Pressed, this, &AEmulatorPlayerController::HandleKeyboardE);

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

	this->MouseSelection(HitActor);
}

void AEmulatorPlayerController::RightClickInteract()
{
	FHitResult HitResult;
	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	if (!this->MouseSelection(HitActor))
	{
		return;
	}

	IPopulateDetailsInterface* ActorInterface = Cast<IPopulateDetailsInterface>(HitActor);
	if (ActorInterface)
	{
		UDetailsPopupWidget* DetailsPopup = Cast<UDetailsPopupWidget>(CreateWidget(this, this->DetailsPopupClass));
		ActorInterface->DetailsPopupInteract(DetailsPopup->GetContentWidget());
		DetailsPopup->SetHeaderText(FText::FromString(HitActor->GetActorNameOrLabel()));

		this->MainHUD->AddDetailsPopup(DetailsPopup);
	}
}

bool AEmulatorPlayerController::MouseSelection(AActor* HitActor)
{
	if (!IsValid(HitActor) || this->CurrentSelection == HitActor)
	{
		return false;
	}

	if (IsValid(this->CurrentSelection))
	{
		// Turn off current selection highlighting.
		UInteractableHighlighting* HighlightComponent = this->GetHighlightingComponent(this->CurrentSelection);
		if (IsValid(HighlightComponent))
		{
			HighlightComponent->SetSelectedDisabled();
		}
	}

	UInteractableHighlighting* HighlightComponent = this->GetHighlightingComponent(HitActor);
	if (IsValid(HighlightComponent))
	{
		HighlightComponent->SetSelectedActive();
		this->CurrentSelection = HitActor;
	}

	return true;
}

UInteractableHighlighting* AEmulatorPlayerController::GetHighlightingComponent(AActor* Actor)
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

void AEmulatorPlayerController::CreateStraightConveyor()
{
	this->CurrentBuildModeState = FBuildModeState::Placing;

	// Spawn dynamic straight conveyor.
	FActorSpawnParameters SpawnParameters;
	FTransform Transform = FTransform::Identity;
	ADynamicStraightConveyor* Conveyor = GetWorld()->SpawnActor<ADynamicStraightConveyor>(this->DynamicStraightConveyorClass, Transform, SpawnParameters);

	if (IsValid(Conveyor))
	{
		// Set position to floor. Follow mouse cursor.
		if (1)
		{
			FVector WorldLocation;
			FVector WorldDirection;
			this->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
			FHitResult OutHit;
			FVector TraceStart = this->CurrentPawn->GetCamera()->GetComponentLocation();
			FVector TraceEnd = WorldLocation + (WorldDirection * 10000);
			FCollisionQueryParams CollisionParams;
			GetWorld()->LineTraceSingleByProfile(OutHit, TraceStart, TraceEnd, FName(TEXT("Floor")), CollisionParams);
			if (IsValid(OutHit.GetActor()))
			{

			}
		}
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
	this->ChangeInteractionMode(FInteractionMode::ObserveMode);
}

void AEmulatorPlayerController::HandleKeyboard2()
{
	this->ChangeInteractionMode(FInteractionMode::InteractMode);
}

void AEmulatorPlayerController::HandleKeyboard3()
{
	this->ChangeInteractionMode(FInteractionMode::BuildMode);
}

void AEmulatorPlayerController::HandleKeyboardF()
{
	this->CurrentPawn->KeyboardF();
}

void AEmulatorPlayerController::HandleKeyboardE()
{
	this->CurrentPawn->KeyboardE();
}

void AEmulatorPlayerController::HandleKeyboardEND()
{
	this->CurrentPawn->KeyboardEND();
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
	this->RightClickInteract();
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