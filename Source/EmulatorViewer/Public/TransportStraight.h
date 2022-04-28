// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransportStraight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMULATORVIEWER_API UTransportStraight : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Constructor
	UTransportStraight();

	// Custom physics delegate
	FCalculateCustomPhysics OnCalculateCustomPhysics;
	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance);

	// Event called every physics tick and sub-step.
	UFUNCTION()
	void PhysicsTick(float SubstepDeltaTime);
	
	UPROPERTY(EditAnywhere, Category = "Conveyor")
	float Speed = 200.0f;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

	FTransform OriginalTransform;
	FVector OriginalLocation;
	FBodyInstance* ConveyorBodyInstance;
	UStaticMeshComponent* ConveyorMesh;
};
