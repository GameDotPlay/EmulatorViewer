

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EmulatorCharacter.generated.h"

UCLASS()
class EMULATORVIEWER_API AEmulatorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmulatorCharacter();

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
};