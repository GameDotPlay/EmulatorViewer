

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EmulatorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API AEmulatorGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

protected:

	virtual void BeginPlay() override;

private:

};
