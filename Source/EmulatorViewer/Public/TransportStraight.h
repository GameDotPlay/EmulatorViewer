// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransportStraight.generated.h"

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

	// Custom physics delegate
	FCalculateCustomPhysics OnCalculateCustomPhysics;
	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance);

	// Event called every physics tick and sub-step.
	UFUNCTION()
	void PhysicsTick(float SubstepDeltaTime);

	// Called every rendering frame.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "Conveyor", DisplayName = "Speed (cm/s)")
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Conveyor")
	EDirection Direction = EDirection::Forward;

protected:

	virtual void BeginPlay() override;

private:

	FTransform OriginalTransform;
	FBodyInstance* ConveyorBodyInstance;

	UPROPERTY(VisibleAnywhere, Category = "Conveyor", DisplayName = "Width (cm)")
	float Width = 152.4f;
};
