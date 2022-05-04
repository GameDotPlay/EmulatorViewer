#include "TransportPowerTurn.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTransportPowerTurn::UTransportPowerTurn()
{
	// Enable this component to tick every frame.
	PrimaryComponentTick.bCanEverTick = true;

	// Bind the custom physics tick.
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
	FVector BoundsOrigin;
	FVector Bounds;
	GetOwner()->GetActorBounds(true, BoundsOrigin, Bounds, false);
	OuterRadius = Bounds.Y * 2;
	Radius.Emplace(OuterRadius - (Width * 0.95f));
	Radius.Emplace(OuterRadius - (Width * 0.5f));
	Radius.Emplace(OuterRadius - (Width * 0.05f));
	AngularMultiplier = Speed / (Radius[(int32)SpeedReference]); // AngularVelocity = DesiredLinearSpeed / Radius;

	// Set center of mass equal to mesh origin. SetAngularVelocityInRadians() in PhysicsTick() always rotates around center of mass.
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
}

void UTransportPowerTurn::PhysicsTick(float SubstepDeltaTime)
{
	this->ConveyorBodyInstance->SetInstanceSimulatePhysics(false);
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision, true);

	// Teleport to the previous transform.
	this->ConveyorBodyInstance->SetBodyTransform(this->OriginalTransform, ETeleportType::TeleportPhysics);

	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	this->ConveyorBodyInstance->SetInstanceSimulatePhysics(true);

	// Rotate around the center of mass.
	this->ConveyorBodyInstance->SetAngularVelocityInRadians((int32)this->Direction * FVector::DownVector * this->AngularMultiplier, false);
}

void UTransportPowerTurn::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance)
{
	PhysicsTick(DeltaTime);
}