

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInterface.h"
#include "FloatingPawnBase.h"
#include "EmulatorGodPawn.generated.h"

UCLASS()
class EMULATORVIEWER_API AEmulatorGodPawn : public AFloatingPawnBase
{
	GENERATED_BODY()

public:

	AEmulatorGodPawn();

	virtual void Tick(float DeltaTime) override;

	void KeyboardF() override;

	void KeyboardE() override;

	void KeyboardEND() override;

	void MouseWheelAxis(float Value) override;

	bool CurrentlyHoldingObject() override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	FVector CameraTargetVector;

	float CameraTargetVectorLength;

	float MinTargetDistance = 300.f;

	float MaxTargetDistance = 1000.f;

	float DistanceAdjustSensitivity = 1000.f;

	void FocusView();

	void Zoom(float Value);

	void PhysicsObjectDistanceAdjust(float Value);

	void GrabPhysicsObject(FHitResult HitResult);

	void ReleasePhysicsObject();
};