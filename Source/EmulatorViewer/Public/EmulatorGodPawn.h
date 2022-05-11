

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EmulatorGodPawn.generated.h"

struct ViewportSize {

	int32 X;
	int32 Y;
};

UCLASS()
class EMULATORVIEWER_API AEmulatorGodPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEmulatorGodPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
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
	float MouseWheelSensitivity = 100.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MinTargetArmLength = 200.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MaxTargetArmLength = 2500.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float WorldMinZ = 1.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool bMouseEdgeScrollEnabled = true;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* LookTarget;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	bool bMiddleMousePressed = false;

	class AEmulatorPlayerController* PlayerController;

	AActor* LastSelected = nullptr;

	FVector2D MousePosition;

	ViewportSize CurrentViewportSize;

	void MiddleMousePressed();

	void MiddleMouseReleased();

	void RotateMouseX(float Value);

	void RotateMouseY(float Value);

	void FocusView();

	void Zoom(float Value);

	void MouseEdgeScroll();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void LeftClickSelect();
};