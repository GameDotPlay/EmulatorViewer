#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInterface.h"
#include "FloatingPawnBase.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	bool bMiddleMouseDown = false;

	APlayerController* PlayerController;

	FVector2D MousePosition;

	FViewportSize CurrentViewportSize;

};
