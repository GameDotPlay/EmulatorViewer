

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransportStraight.generated.h"

#define CENTIMETERSTOFEET 1.f / 30.48f

UENUM()
enum class EDirection : int32
{
	Forward = 1,
	Reverse = -1
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMULATORVIEWER_API UTransportStraight : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTransportStraight();

	FCalculateCustomPhysics OnCalculateCustomPhysics;
	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance);

	UFUNCTION()
	void PhysicsTick(float SubstepDeltaTime);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "Conveyor", DisplayName = "Speed (cm/s)")
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Conveyor")
	EDirection Direction = EDirection::Forward;

	float GetSpeedFPM() const { return this->Speed * 60.f * CENTIMETERSTOFEET; }

protected:

	virtual void BeginPlay() override;

private:

	FTransform OriginalTransform;
	FBodyInstance* ConveyorBodyInstance = nullptr;
	UStaticMeshComponent* ConveyorMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Conveyor", DisplayName = "Width (cm)")
	float Width = 152.4f;

	float AccelerationFactor = 1.f;
};
