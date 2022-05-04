#include "TransportStraight.h"

// Sets default values for this component's properties
UTransportStraight::UTransportStraight()
{
	// Enable this component to tick every frame.
	PrimaryComponentTick.bCanEverTick = true;

	OnCalculateCustomPhysics.BindUObject(this, &UTransportStraight::CustomPhysics);
}

// Called when the game starts
void UTransportStraight::BeginPlay()
{
	Super::BeginPlay();

	// Cache references.
	this->ConveyorBodyInstance = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent())->GetBodyInstance();
	this->OriginalTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();
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
	this->ConveyorBodyInstance->SetInstanceSimulatePhysics(false);
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision, true);

	// Teleport to previous transform.
	this->ConveyorBodyInstance->SetBodyTransform(this->OriginalTransform, ETeleportType::TeleportPhysics, true);
	
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	this->ConveyorBodyInstance->SetInstanceSimulatePhysics(true);

	// Translate forward.
	this->ConveyorBodyInstance->SetLinearVelocity((int32)this->Direction * FVector::ForwardVector * Speed, false, true);
}

void UTransportStraight::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance) 
{
	PhysicsTick(DeltaTime);
}