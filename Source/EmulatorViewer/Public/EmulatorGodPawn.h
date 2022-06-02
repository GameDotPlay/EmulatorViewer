

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInterface.h"
#include "EmulatorGodPawn.generated.h"

struct ViewportSize {

	int32 X;
	int32 Y;
};

UCLASS()
class EMULATORVIEWER_API AEmulatorGodPawn : public APawn, public IPawnInterface
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

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int32 ScreenEdgeBuffer = 10.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MouseEdgeScrollSpeed = 2000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool bInvertMouseX = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool bInvertMouseY = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MinPitchValue = -10.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MaxPitchValue = 55.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MouseRotateSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MouseWheelSensitivity = 10000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MinTargetArmLength = 200.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MaxTargetArmLength = 2500.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float WorldMinZ = 1.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool bMouseEdgeScrollEnabled = true;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* LookTarget = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	bool bMiddleMousePressed = false;

	APlayerController* PlayerController;

	FVector2D MousePosition;

	FVector CameraTargetVector;

	float CameraTargetVectorLength;

	float MinTargetDistance = 300.f;

	float MaxTargetDistance = 1000.f;

	float DistanceAdjustSensitivity = 1000.f;

	ViewportSize CurrentViewportSize;

	void FocusView(FVector Location);

	void Zoom(float Value);

	void MouseEdgeScroll();

	void PhysicsObjectDistanceAdjust(float Value);

	void GrabPhysicsObject(FHitResult HitResult);
};