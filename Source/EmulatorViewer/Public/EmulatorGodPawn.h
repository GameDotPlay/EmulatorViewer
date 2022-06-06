

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInterface.h"
#include "FloatingPawnBase.h"
#include "EmulatorGodPawn.generated.h"

UCLASS()
class EMULATORVIEWER_API AEmulatorGodPawn : public APawn, public AFloatingPawnBase, public IPawnInterface
{
	GENERATED_BODY()

public:

	AEmulatorGodPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void MiddleMousePressed() override;

	virtual void MiddleMouseReleased() override;

	virtual void KeyboardF(FVector Location) override;

	virtual void KeyboardE(FHitResult HitResult) override;

	virtual void KeyboardEND(float NewZ) override;

	virtual void MoveForward(float Value) override;

	virtual void MoveRight(float Value) override;

	virtual void MouseXAxis(float Value) override;

	virtual void MouseYAxis(float Value) override;

	virtual void MouseWheelAxis(float Value) override;

	virtual bool CurrentlyHoldingObject() override;

	virtual void ReleasePhysicsObject() override;

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

	void FocusView(FVector Location);

	void Zoom(float Value);

	void MouseEdgeScroll();

	void PhysicsObjectDistanceAdjust(float Value);

	void GrabPhysicsObject(FHitResult HitResult);
};