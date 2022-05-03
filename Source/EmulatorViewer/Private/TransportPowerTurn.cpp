#include "TransportPowerTurn.h"

#define PI 3.141592

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

	this->ConveyorMesh = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent());
	this->ConveyorBodyInstance = this->ConveyorMesh->GetBodyInstance();

	this->OriginalTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();
	this->OriginalRotation = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetRotation().Rotator();
	this->OriginalLocation = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetLocation();

	this->AngularMultiplier = 1 / (this->Radius * (PI / 180));
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
	//this->ConveyorMesh->SetSimulatePhysics(false);
	//this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision, true);
	//const FVector Forward = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetUnitAxis(EAxis::X);

	FQuat DeltaRotation = FQuat::MakeFromEuler((-1.f * FVector(0.f, 0.f, 1.f) * AngularMultiplier) * Speed * SubstepDeltaTime);
	FQuat UndoRotation = FQuat::MakeFromEuler((-1.f * -FVector(0.f, 0.f, 1.f) * AngularMultiplier) * Speed * SubstepDeltaTime);

	FQuat CurrentRotation = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetRotation();
	FTransform NewTransform = this->ConveyorBodyInstance->GetUnrealWorldTransform();
	NewTransform.SetRotation(CurrentRotation * DeltaRotation);
	this->ConveyorBodyInstance->SetBodyTransform(NewTransform, ETeleportType::ResetPhysics);
	
	//this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly, true);
	//this->ConveyorMesh->SetSimulatePhysics(true);

	//this->ConveyorBodyInstance->SetAngularVelocityInRadians(FVector(0.f, 0.f, 100.f * SubstepDeltaTime), false);
}

void UTransportPowerTurn::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance)
{
	PhysicsTick(DeltaTime);
}