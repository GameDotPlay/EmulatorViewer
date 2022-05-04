#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransportPowerTurn.generated.h"

#define CENTIMETERS_TO_FEET 1 / 30.48
#define CENTIMETERS_TO_INCHES 1 / 2.54

UENUM()
enum class ESpeedReference : int32
{
	Inside = 0,
	Middle = 1,
	Outside = 2
};

UENUM()
enum class EDirection : int32
{
	LeftTurn = 1,
	RightTurn = -1
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMULATORVIEWER_API UTransportPowerTurn : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTransportPowerTurn();

	// Called every frame
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

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	FTransform OriginalTransform;
	FBodyInstance* ConveyorBodyInstance = nullptr;
	float AngularMultiplier;
	TArray<float> Radius;
	FVector BoundsOrigin;
	FVector Bounds;

	UPROPERTY(VisibleAnywhere, Category = "Conveyor")
	EDirection Direction = EDirection::RightTurn;

	UPROPERTY(VisibleAnywhere, Category = "Conveyor", DisplayName = "Width (cm)")
	float Width = 152.4f;
};