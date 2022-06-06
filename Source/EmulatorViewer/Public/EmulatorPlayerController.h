#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EmulatorPlayerController.generated.h"

class AEmulatorViewerHUD;
class AEmulatorGodPawn;
class UInteractableHighlighting;
class UUserWidget;

UENUM()
enum class FControlMode
{
	FirstPerson = 0,
	GodMode = 1
};

UENUM()
enum class FInteractionMode
{
	FullMenuMode = 0,
	PopupMenuMode = 1,
	ObserveMode = 2,
	InteractMode = 3,
	BuildMode = 4
};

UENUM()
enum class FBuildModeState
{
	NotBuilding = 0,
	Placing = 1,
	Modifying = 2
};

UCLASS()
class EMULATORVIEWER_API AEmulatorPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:

	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DetailsPopupClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DynamicStraightConveyorClass;

	AEmulatorViewerHUD* MainHUD;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float FloorZOffset = 50.f;

	float FloorZ = 0.f;

	AActor* CurrentSelection = nullptr;

	AEmulatorGodPawn* CurrentPawn = nullptr;

	FControlMode CurrentControlMode;

	FInteractionMode CurrentInteractionMode;

	FBuildModeState CurrentBuildModeState;

	virtual void SetupInputComponent() override;

	void ToggleControlMode();

	void SetGodControlMode();

	void SetFirstPersonControlMode();

	void ChangeInteractionMode(FInteractionMode NewInteractionMode);

	void SetFullMenuInteractionMode();

	void SetPopupMenuInteractionMode();

	void SetObserveInteractionMode();

	void SetInteractInteractionMode();

	void SetBuildInteractionMode();

	FInputModeGameAndUI GetDefaultInputMode();

	void LeftClickSelect();

	void RightClickInteract();

	bool MouseSelection(AActor* HitActor);

	UInteractableHighlighting* GetHighlightingComponent(AActor* Actor);

	void CreateStraightConveyor();

#pragma region InputBindings

	void HandleKeyboard1();

	void HandleKeyboard2();

	void HandleKeyboard3();

	void HandleKeyboardF();

	void HandleKeyboardEND();

	void HandleKeyboardE();

	void HandleMiddleMouseButtonPressed();

	void HandleMiddleMouseButtonReleased();

	void HandleLeftMouseButton();

	void HandleRightMouseButton();

	void HandleMouseWheel(float Value);

	void HandleMouseXAxis(float Value);

	void HandleMouseYAxis(float Value);

	void HandleForwardAxis(float Value);

	void HandleRightAxis(float Value);

#pragma endregion
};