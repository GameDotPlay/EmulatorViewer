
#include "TransportPowerTurn.h"
#include "DrawDebugHelpers.h"

UTransportPowerTurn::UTransportPowerTurn()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Bind the custom physics tick.
	OnCalculateCustomPhysics.BindUObject(this, &UTransportPowerTurn::CustomPhysics);
}

void UTransportPowerTurn::BeginPlay()
{
	Super::BeginPlay();

	// Cache references.
	this->ConveyorMesh = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent());
	TArray<UActorComponent*> Components;
	Components = this->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName(TEXT("PhysicsMesh")));
	if (Components.Num() > 0 && IsValid(Components[0]))
	{
		this->ConveyorBodyInstance = Cast<UStaticMeshComponent>(Components[0])->GetBodyInstance();
	}

	this->OriginalTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();

	// Calculate radius of power turn. This affects the calculation of angular velocity depending on speed reference setting.
	FVector BoundsOrigin;
	FVector Bounds;
	GetOwner()->GetActorBounds(true, BoundsOrigin, Bounds, false);
	OuterRadius = Bounds.Y * 2;
	Radius.Emplace(OuterRadius - (Width * 0.95f));
	Radius.Emplace(OuterRadius - (Width * 0.5f));
	Radius.Emplace(OuterRadius - (Width * 0.05f));
	AngularMultiplier = (this->Speed * this->AccelerationFactor) / (Radius[(int32)SpeedReference]); // AngularVelocity = DesiredLinearSpeed / Radius;

	// Set center of mass equal to mesh origin. SetAngularVelocityInRadians() in PhysicsTick() always rotates around center of mass.
	FVector COMOffset = (OriginalTransform.GetLocation() - ConveyorBodyInstance->GetCOMPosition());
	FRotator Rotation = OriginalTransform.GetRotation().Rotator();
	COMOffset = COMOffset.RotateAngleAxis(-Rotation.Yaw, FVector::UpVector); // Remove any rotation the mesh may have from the calculation of COMOffset.
	ConveyorBodyInstance->COMNudge = COMOffset;
	ConveyorBodyInstance->UpdateMassProperties();
}

// Called every frame
void UTransportPowerTurn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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