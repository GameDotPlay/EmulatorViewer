#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransportPowerTurn.generated.h"

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

	UPROPERTY(EditAnywhere, Category = "Conveyor")
	float Speed = 200.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	FTransform OriginalTransform;
	FRotator OriginalRotation;
	FBodyInstance* ConveyorBodyInstance = nullptr;
	UStaticMeshComponent* ConveyorMesh = nullptr;

	float Radius = 228.6f;
	float AngularMultiplier;
};