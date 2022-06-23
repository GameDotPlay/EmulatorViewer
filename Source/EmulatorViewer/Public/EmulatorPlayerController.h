#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EmulatorPlayerController.generated.h"

class AEmulatorViewerHUD;
class AEmulatorGodPawn;
class UInteractableHighlighting;
class UUserWidget;
class IPawnInterface;
class ABuildModePawn;
class AEmulatorFPCharacter;

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

	AEmulatorViewerHUD* GetMainHUD() const { return this->MainHUD; }

	void TogglePause();

protected:

	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DynamicStraightConveyorClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEmulatorGodPawn> DefaultGodPawnClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABuildModePawn> BuildModePawnClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEmulatorFPCharacter> FirstPersonPawnClass;

	AEmulatorViewerHUD* MainHUD;

	IPawnInterface* CurrentPawn = nullptr;

	FControlMode CurrentControlMode;

	FInteractionMode CurrentInteractionMode;

	FInteractionMode LastInteractionMode;

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

	void CreateStraightConveyor();

#pragma region InputBindings

	void HandleKeyboard1();

	void HandleKeyboard2();

	void HandleKeyboard3();

	void HandleKeyboardF();

	void HandleKeyboardEND();

	void HandleKeyboardESC();

	void HandleKeyboardE();

	void HandleKeyboardSPACE();

	void HandleMiddleMouseButtonPressed();

	void HandleMiddleMouseButtonReleased();

	void HandleLeftMouseButton();

	void HandleRightMouseButton();

	void HandleMouseWheel(float Value);

	void HandleMouseXAxis(float Value);

	void HandleMouseYAxis(float Value);

	void HandleForwardAxis(float Value);

	void HandleRightAxis(float Value);

	void HandleUpAxis(float Value);

#pragma endregion
};