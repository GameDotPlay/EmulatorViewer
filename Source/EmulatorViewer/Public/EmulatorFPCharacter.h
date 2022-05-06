

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EmulatorFPCharacter.generated.h"

UCLASS()
class EMULATORVIEWER_API AEmulatorFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmulatorFPCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	void MoveForward(float Value);

	void StrafeRight(float Value);
};