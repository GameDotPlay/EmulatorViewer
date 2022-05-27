
#include "TransportStraight.h"

UTransportStraight::UTransportStraight()
{
	PrimaryComponentTick.bCanEverTick = true;

	OnCalculateCustomPhysics.BindUObject(this, &UTransportStraight::CustomPhysics);
}

// Called when the game starts
void UTransportStraight::BeginPlay()
{
	Super::BeginPlay();

	// Cache references.
	this->OwnerRoot = Cast<USceneComponent>(this->GetOwner()->GetRootComponent());
	TArray<UActorComponent*> Components;
	Components = this->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName(TEXT("PhysicsMesh")));
	if (Components.Num() > 0 && IsValid(Components[0]))
	{
		this->ConveyorMesh = Cast<UStaticMeshComponent>(Components[0]);
		this->ConveyorBodyInstance = this->ConveyorMesh->GetBodyInstance();
	}

	this->OriginalTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();
}

void UTransportStraight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Still WIP. Speed of texture doesn't quite match up to item speed on belt. Texture is too slow.
	float MaterialPanSpeed = this->Speed * this->AccelerationFactor / 100.f;
	this->ConveyorMesh->SetVectorParameterValueOnMaterials(FName("PanSpeed"), FVector(0, MaterialPanSpeed, 0));

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
	this->ConveyorBodyInstance->SetLinearVelocity((int32)this->Direction * this->OwnerRoot->GetForwardVector() * this->Speed * this->AccelerationFactor, false, true);
}

void UTransportStraight::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance) 
{
	PhysicsTick(DeltaTime);
}