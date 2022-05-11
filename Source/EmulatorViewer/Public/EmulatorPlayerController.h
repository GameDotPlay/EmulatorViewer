#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EmulatorPlayerController.generated.h"

class AEmulatorFPCharacter;
class AEmulatorGodPawn;

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

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEmulatorFPCharacter> FirstPersonCharacter = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEmulatorGodPawn> GodModeCharacter = nullptr;

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

	FControlMode CurrentControlMode;

	FInteractionMode CurrentInteractionMode;

	AActor* CurrentSelection;
};