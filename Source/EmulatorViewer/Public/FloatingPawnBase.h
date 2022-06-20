#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInterface.h"
#include "FloatingPawnBase.generated.h"

class AEmulatorPlayerController;

struct FViewportSize {

	int32 X;
	int32 Y;
};

UCLASS()
class EMULATORVIEWER_API AFloatingPawnBase : public APawn, public IPawnInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFloatingPawnBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UCameraComponent* GetCamera() override { return this->Camera; }

	virtual void MiddleMousePressed() override;

	virtual void MiddleMouseReleased() override;

	virtual void MoveForward(float Value) override;

	virtual void MoveRight(float Value) override;

	virtual void MoveUp(float Value) override;

	virtual void MouseXAxis(float Value) override;

	virtual void MouseYAxis(float Value) override;

protected:

	virtual void BeginPlay() override;

	virtual void MouseEdgeScroll();

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* LookTarget = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera = nullptr;

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

	AEmulatorPlayerController* PlayerController;

	FVector2D MousePosition;

	FViewportSize CurrentViewportSize;

	bool bMiddleMouseDown = false;

	float FloorZ = 0.f;

	float FloorZOffset = 50.f;
};
