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
	this->ConveyorMesh->SetSimulatePhysics(false);
	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::NoCollision, true);
	FVector Forward = this->ConveyorBodyInstance->GetUnrealWorldTransform().GetUnitAxis(EAxis::X);
	FVector Backward = -this->ConveyorBodyInstance->GetUnrealWorldTransform().GetUnitAxis(EAxis::X);

	//deltaRotation = Quaternion.Euler(((int)direction * Vector3.forward * angularMultiplier) * speed * Time.fixedDeltaTime);
	//undoRotation = Quaternion.Euler(((int)direction * Vector3.back * angularMultiplier) * speed * Time.fixedDeltaTime);
	//rb.rotation = rb.rotation * deltaRotation;
	//rb.MoveRotation(rb.rotation * undoRotation);

	FQuat DeltaRotation = FQuat::MakeFromEuler((-1.f * Forward * AngularMultiplier) * Speed * SubstepDeltaTime);
	FQuat UndoRotation = FQuat::MakeFromEuler((1.f * Backward * AngularMultiplier) * Speed * SubstepDeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("DeltaRotation: <%f, %f, %f>"), DeltaRotation.Rotator().Pitch, DeltaRotation.Rotator().Yaw, DeltaRotation.Rotator().Roll);

	// Teleport backwards rotation.
	FTransform NewTransform = this->OriginalTransform;
	NewTransform.SetRotation(DeltaRotation);
	this->ConveyorBodyInstance->SetBodyTransform(NewTransform, ETeleportType::TeleportPhysics, true);

	this->ConveyorBodyInstance->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly, true);
	this->ConveyorMesh->SetSimulatePhysics(true);

	// Set angular velocity.
	FVector ForwardRotation = UndoRotation.Euler();

	UE_LOG(LogTemp, Warning, TEXT("ForwardRotation: <%f, %f, %f>"), ForwardRotation.X, ForwardRotation.Y, ForwardRotation.Z);

	this->ConveyorBodyInstance->SetAngularVelocityInRadians(ForwardRotation, false);
}

void UTransportPowerTurn::CustomPhysics(float DeltaTime, FBodyInstance* BodyInstance)
{
	PhysicsTick(DeltaTime);
}