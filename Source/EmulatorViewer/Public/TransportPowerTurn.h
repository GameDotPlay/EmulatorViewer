#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransportPowerTurn.generated.h"

#define CENTIMETERSTOFEET 1.f / 30.48f


UENUM()
enum class ESpeedReference : int32
{
	Inside = 0,
	Middle = 1,
	Outside = 2
};

UENUM()
enum class EDirectionType : int32
{
	LeftTurn = 1,
	RightTurn = -1
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMULATORVIEWER_API UTransportPowerTurn : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTransportPowerTurn();

	// Called every rendering frame.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Custom physics delegate
	FCalculateCustomPhysics OnCalculateCustomPhysics;
	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance);

	// Event called every physics tick and sub-step.
	UFUNCTION()
	void PhysicsTick(float SubstepDeltaTime);

	UPROPERTY(EditAnywhere, Category = "Conveyor", DisplayName = "Speed (cm/s)")
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Conveyor")
	ESpeedReference SpeedReference = ESpeedReference::Middle;

	float GetSpeedFPM() const { return this->Speed * 60.f * CENTIMETERSTOFEET; }

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	FTransform OriginalTransform;

	FBodyInstance* ConveyorBodyInstance = nullptr;

	UStaticMeshComponent* ConveyorMesh = nullptr;

	float AngularMultiplier;

	TArray<float> Radius;

	float OuterRadius;

	UPROPERTY(VisibleAnywhere, Category = "Conveyor")
	EDirectionType Direction = EDirectionType::RightTurn;

	UPROPERTY(VisibleAnywhere, Category = "Conveyor", DisplayName = "Width (cm)")
	float Width = 152.4f;

	float AccelerationFactor = 1.f;
};