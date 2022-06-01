

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EMULATORVIEWER_API IPawnInterface
{
	GENERATED_BODY()

public:

	virtual void MiddleMousePressed() { return; }

	virtual void MiddleMouseReleased() { return; }

	virtual void KeyboardF(FVector Location) { return; }

	virtual void KeyboardE(FHitResult HitResult) { return; }

	virtual void KeyboardEND(float NewZ) { return; }

	virtual void MoveForward(float Value) { return; }

	virtual void MoveRight(float Value) { return; }

	virtual void MouseXAxis(float Value) { return; }

	virtual void MouseYAxis(float Value) { return; }

	virtual void MouseWheelAxis(float Value) { return; }
};