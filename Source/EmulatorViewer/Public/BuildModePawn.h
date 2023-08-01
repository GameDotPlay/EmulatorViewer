/*****************************************************************//**
 * @file   BuildModePawn.h
 * @brief  Class file for BuildModePwn
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "FloatingPawnBase.h"
#include "BuildModePawn.generated.h"

/** Enum defining the current state the BuildModePawn is in. */
UENUM()
enum class FBuildModeState
{
	/** Currently not placing/building anything. */
	NotBuilding = 0,

	/** Currently placing/building something. */
	Placing = 1,

	/** Currently modifying something. */
	Modifying = 2
};

/** Class for the BuildModePawn. */
UCLASS()
class EMULATORVIEWER_API ABuildModePawn : public AFloatingPawnBase
{
	GENERATED_BODY()

public:

protected:

private:

};