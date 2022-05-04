#include "TransportPowerTurn.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTransportPowerTurn::UTransportPowerTurn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OnCalculateCustomPhysics.BindUObject(this, &UTransportPowerTurn::CustomPhysics);
}

// Called when the game starts
void UTransportPowerTurn::BeginPlay()
{
	Super::BeginPlay();

	// Cache references.
	this->ConveyorBodyInstance = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent())->GetBodyInstance();
	this->OriginalTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();

	// Calculate radius of power turn. This affects the calculation of angular velocity depending on speed reference setting.
	GetOwner()->GetActorBounds(true, BoundsOrigin, Bounds, false);

	// Set center of mass equal to mesh origin.
	FVector COMOffset = GetOwner()->GetActorLocation() - ConveyorBodyInstance->GetCOMPosition();
	ConveyorBodyInstance->COMNudge = COMOffset;
	ConveyorBodyInstance->UpdateMassProperties();
}

// Called every frame
void UTransportPowerTurn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Add custom physics on RootComponent's BodyInstance
	if (this->ConveyorBodyInstance)
	{
		this->ConveyorBodyInstance->AddCustomPhysics(this->OnCalculateCustomPhysics);
	}

	DrawDebugBox(GetWorld(), BoundsOrigin, Bounds, ConveyorBodyInstance->GetUnrealWorldTransform().GetRotation(), FColor::Green, false, -1.f, 0, 5.f);
}

void UTransportPowerTurn::PhysicsTick(float SubstepDeltaTime)
{
	this->ConveyorBodyInstance->SetInstanceSimulatePhysics(false);
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision, true);

	this->ConveyorBodyInstance->SetBodyTransform(OriginalTransform, ETeleportType::TeleportPhysics);

	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	this->ConveyorBodyInstance->SetInstanceSimulatePhysics(true);

	ConveyorBodyInstance->SetAngularVelocityInRadians(FVector(0.f, 0.f, 100.f * SubstepDeltaTime), false);
}

void UTransportPowerTurn::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance)
{
	PhysicsTick(DeltaTime);
}