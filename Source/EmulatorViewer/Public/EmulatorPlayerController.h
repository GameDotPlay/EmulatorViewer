#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EmulatorPlayerController.generated.h"



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

UCLASS()
class EMULATORVIEWER_API AEmulatorPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainHUDWidget> MainHUDWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float FloorZOffset = 50.f;

	float FloorZ = 0.f;

	UMainHUDWidget* MainHUD = nullptr;

	AActor* CurrentSelection = nullptr;

	class AEmulatorGodPawn* CurrentPawn = nullptr;

	FControlMode CurrentControlMode;

	FInteractionMode CurrentInteractionMode;

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

	class UInteractableHighlighting* GetInteractableComponent(AActor* Actor);

#pragma region InputBindings

	void HandleKeyboard1();

	void HandleKeyboard2();

	void HandleKeyboard3();

	void HandleKeyboardF();

	void HandleKeyboardEND();

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