

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

class UCameraComponent;

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

	virtual void LeftMouseClick() { return; }

	virtual void RightMouseClick() { return; }

	virtual void MouseXAxis(float Value) { return; }

	virtual void MouseYAxis(float Value) { return; }

	virtual void MouseWheelAxis(float Value) { return; }

	virtual void KeyboardF() { return; }

	virtual void KeyboardE() { return; }

	virtual void KeyboardEND() { return; }

	virtual void KeyboardESC() { return; }

	virtual void KeyboardSPACE() { return; }

	virtual void MoveForward(float Value) { return; }

	virtual void MoveRight(float Value) { return; }

	virtual void MoveUp(float Value) { return; }

	virtual void MoveDown(float Value) { return; }

	virtual bool CurrentlyHoldingObject() { return false; }

	virtual UCameraComponent* GetCamera() const { return nullptr; }

	virtual FTransform GetTransform() const { return FTransform::Identity; }

	virtual bool DestroyPawn(bool bNetForce = false, bool bShouldModifyLevel = true) { return false; }
};