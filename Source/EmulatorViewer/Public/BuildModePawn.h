#pragma once

#include "CoreMinimal.h"
#include "FloatingPawnBase.h"
#include "BuildModePawn.generated.h"

UENUM()
enum class FBuildModeState
{
	NotBuilding = 0,
	Placing = 1,
	Modifying = 2
};

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API ABuildModePawn : public AFloatingPawnBase
{
	GENERATED_BODY()

public:

protected:

private:

};