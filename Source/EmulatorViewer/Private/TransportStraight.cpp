// Fill out your copyright notice in the Description page of Project Settings.

#include "TransportStraight.h"

// Sets default values for this component's properties
UTransportStraight::UTransportStraight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OnCalculateCustomPhysics.BindUObject(this, &UTransportStraight::CustomPhysics);
}

// Called when the game starts
void UTransportStraight::BeginPlay()
{
	Super::BeginPlay();

	this->ConveyorMesh = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent());
	this->ConveyorBodyInstance = this->ConveyorMesh->GetBodyInstance();

	this->OriginalTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();
	this->OriginalLocation = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetLocation();
}

// Called every frame
void UTransportStraight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Add custom physics on RootComponent's BodyInstance
	if (this->ConveyorBodyInstance) 
	{
		this->ConveyorBodyInstance->AddCustomPhysics(this->OnCalculateCustomPhysics);
	}
}

void UTransportStraight::PhysicsTick(float SubstepDeltaTime)
{
	this->ConveyorMesh->SetSimulatePhysics(false);
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision, true);
	const FVector Forward = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetUnitAxis(EAxis::X);

	// Teleport backwards.
	FTransform NewTransform = this->OriginalTransform;
	NewTransform.SetTranslation(this->OriginalLocation - (Forward * Speed));
	
	this->ConveyorBodyInstance->SetBodyTransform(NewTransform, ETeleportType::TeleportPhysics, true);
	
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly, true);
	this->ConveyorMesh->SetSimulatePhysics(true);

	// Translate forward.
	this->ConveyorBodyInstance->SetLinearVelocity(Forward * Speed, false, true);
}

void UTransportStraight::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance) 
{
	PhysicsTick(DeltaTime);
}