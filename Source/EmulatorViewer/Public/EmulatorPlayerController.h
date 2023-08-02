/*****************************************************************//**
 * @file   EmulatorPlayerController.h
 * @brief  Class file for EmulatorPlayerController
 * 
 * @author Erich Smith
 * @date   August 02, 2023
 *********************************************************************/
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

/** The current control state the player is in. */
UENUM()
enum class FControlMode
{
	FirstPerson = 0,
	GodMode = 1
};

/** The current state of the interaction mode. */
UENUM()
enum class FInteractionMode
{
	FullMenuMode = 0,
	PopupMenuMode = 1,
	ObserveMode = 2,
	InteractMode = 3,
	BuildMode = 4
};

/** The PlayerController class. */
UCLASS()
class EMULATORVIEWER_API AEmulatorPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	/**
	 * Get a reference to the MainHUD.
	 */
	AEmulatorViewerHUD* GetMainHUD() const { return this->MainHUD; }

	/**
	 * Toggle the pause state.
	 */
	void TogglePause();

protected:

	/**
	 * Called after all initialization and before the first Tick().
	 */
	virtual void BeginPlay() override;

private:

	/** Reference to the DynamicStraightConveyor class. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DynamicStraightConveyorClass;

	/** Reference to the EmulatorGodPawn class. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEmulatorGodPawn> DefaultGodPawnClass;

	/** Reference to the BuildModePawnClass. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABuildModePawn> BuildModePawnClass;

	/** Reference to the EmunlatorFPCharacter class. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEmulatorFPCharacter> FirstPersonPawnClass;

	/** Reference to the MainHUD. */
	AEmulatorViewerHUD* MainHUD;

	/** Interface to the CurrentPawn. */
	IPawnInterface* CurrentPawn = nullptr;

	/** The current ControlMode. */
	FControlMode CurrentControlMode;

	/** The current InteractionMode. */
	FInteractionMode CurrentInteractionMode;

	/** The last InteractionMode. */
	FInteractionMode LastInteractionMode;

	/**
	 * Binds input to actions.
	 */
	virtual void SetupInputComponent() override;

	/**
	 * Toggles the current control mode between first person and god mode.
	 */
	void ToggleControlMode();

	/**
	 * Sets the current ControlMode to god mode.
	 */
	void SetGodControlMode();

	/**
	 * Sets the current ControlMode to first person mode.
	 */
	void SetFirstPersonControlMode();

	/**
	 * Change the current InteractionMode to the mode given.
	 * @param NewInteractionMode The InteractionMode to switch to
	 */
	void ChangeInteractionMode(FInteractionMode NewInteractionMode);

	/**
	 * Sets the InteractionMode to FullMenu.
	 */
	void SetFullMenuInteractionMode();

	/**
	 * Sets the InteractionMode to Popup.
	 */
	void SetPopupMenuInteractionMode();

	/**
	 * Sets the InteractionMode to Observe.
	 */
	void SetObserveInteractionMode();

	/**
	 * Sets the InteractionMode to Interact.
	 */
	void SetInteractInteractionMode();

	/**
	 * Sets the InteractionMode to Build.
	 */
	void SetBuildInteractionMode();

	/**
	 * Get the default InputMode.
	 */
	FInputModeGameAndUI GetDefaultInputMode();

	/**
	 * Spawn a new straight conveyor.
	 */
	void CreateStraightConveyor();

#pragma region InputBindings

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboard1();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboard2();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboard3();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboardF();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboardEND();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboardESC();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboardE();

	/**
	 * Process keyboard input.
	 */
	void HandleKeyboardSPACE();

	/**
	 * Process mouse input.
	 */
	void HandleMiddleMouseButtonPressed();

	/**
	 * Process mouse input.
	 */
	void HandleMiddleMouseButtonReleased();

	/**
	 * Process mouse input.
	 */
	void HandleLeftMouseButton();

	/**
	 * Process mouse input.
	 */
	void HandleRightMouseButton();

	/**
	 * Process mouse input.
	 */
	void HandleMouseWheel(float Value);

	/**
	 * Process mouse input.
	 */
	void HandleMouseXAxis(float Value);

	/**
	 * Process mouse input.
	 */
	void HandleMouseYAxis(float Value);

	/**
	 * Process keyboard input.
	 */
	void HandleForwardAxis(float Value);

	/**
	 * Process keyboard input.
	 */
	void HandleRightAxis(float Value);

	/**
	 * Process keyboard input.
	 */
	void HandleUpAxis(float Value);

#pragma endregion
};
