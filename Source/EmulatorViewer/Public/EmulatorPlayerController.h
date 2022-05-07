

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EmulatorPlayerController.generated.h"

class AEmulatorFPCharacter;
class AEmulatorGodPawn;

UENUM()
enum class ControlMode
{
	FirstPerson = 0,
	GodMode = 1
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

	void SetupGodMode();

	void SetupFirstPersonMode();

	void ChangeControlMode();

	ControlMode CurrentControlMode;
};