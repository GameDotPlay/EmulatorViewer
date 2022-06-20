
#include "EmulatorGodPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EmulatorPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

AEmulatorGodPawn::AEmulatorGodPawn()
{
	this->PhysicsHandle = Super::CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");

	PhysicsHandle->LinearDamping = 30000.f;
	PhysicsHandle->LinearStiffness = 100000.f;
	PhysicsHandle->AngularDamping = 50000.f;
	PhysicsHandle->AngularStiffness = 200000.f;
	PhysicsHandle->InterpolationSpeed = 17.f;
}

void AEmulatorGodPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AEmulatorGodPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent))
	{
		FVector WorldLocation;
		FVector WorldDirection;
		this->PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		this->CameraTargetVector = WorldLocation + (WorldDirection * this->CameraTargetVectorLength);
		this->PhysicsHandle->SetTargetLocation(this->CameraTargetVector);
	}
}

void AEmulatorGodPawn::KeyboardF()
{
	this->FocusView();
}

void AEmulatorGodPawn::KeyboardE()
{
	// If already holding something, release it.
	if (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent))
	{
		this->ReleasePhysicsObject();
		return;
	}

	// If not already holding something, get hit result under cursor and grab it.
	FHitResult HitResult;
	this->PlayerController->GetHitResultUnderCursor(ECC_PhysicsBody, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	if (IsValid(HitActor) && HitActor->ActorHasTag(FName(TEXT("Item"))))
	{
		if (IsValid(this->PhysicsHandle) && !IsValid(this->PhysicsHandle->GrabbedComponent))
		{
			this->GrabPhysicsObject(HitResult);
			return;
		}
	}
}

void AEmulatorGodPawn::GrabPhysicsObject(FHitResult HitResult)
{
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* HitActor = HitResult.GetActor();

	if (!IsValid(HitActor))
	{
		return;
	}

	if (!IsValid(this->PhysicsHandle))
	{
		return;
	}

	this->PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, HitActor->GetActorLocation(), FRotator::ZeroRotator);
	this->CameraTargetVector = HitActor->GetActorLocation() - this->Camera->GetComponentLocation();
	this->CameraTargetVectorLength = this->CameraTargetVector.Length() - 50.f;
	this->PlayerController->CurrentMouseCursor = EMouseCursor::GrabHandClosed;
}

void AEmulatorGodPawn::ReleasePhysicsObject()
{
	if (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent))
	{
		this->PhysicsHandle->ReleaseComponent();
		this->PlayerController->CurrentMouseCursor = EMouseCursor::GrabHand;
	}
}

void AEmulatorGodPawn::KeyboardEND()
{
	Super::SetActorLocation(FVector(Super::GetActorLocation().X, Super::GetActorLocation().Y, this->FloorZ + this->FloorZOffset));
}

void AEmulatorGodPawn::KeyboardESC()
{

}

void AEmulatorGodPawn::MouseWheelAxis(float Value)
{
	if (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent))
	{
		this->PhysicsObjectDistanceAdjust(Value);
	}
	else
	{
		this->Zoom(Value);
	}
}

bool AEmulatorGodPawn::CurrentlyHoldingObject()
{
	return (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent));
}

void AEmulatorGodPawn::FocusView()
{
	AActor* CurrentSelection = this->PlayerController->GetCurrentSelection();
	if (IsValid(CurrentSelection))
	{
		FVector SelectionExtents;
		FVector SelectionOrigin;
		CurrentSelection->GetActorBounds(true, SelectionOrigin, SelectionExtents, true);
		Super::SetActorLocation(SelectionOrigin);
	}
}

void AEmulatorGodPawn::Zoom(float Value)
{
	this->SpringArm->TargetArmLength -= Value * Super::GetWorld()->GetDeltaSeconds() * this->MouseWheelSensitivity;

	if (this->SpringArm->TargetArmLength < MinTargetArmLength)
	{
		this->SpringArm->TargetArmLength = this->MinTargetArmLength;
	}
	else if (this->SpringArm->TargetArmLength > MaxTargetArmLength)
	{
		this->SpringArm->TargetArmLength = this->MaxTargetArmLength;
	}
}

void AEmulatorGodPawn::PhysicsObjectDistanceAdjust(float Value)
{
	this->CameraTargetVectorLength += Value * Super::GetWorld()->GetDeltaSeconds() * this->DistanceAdjustSensitivity;

	if (this->CameraTargetVectorLength < this->MinTargetDistance)
	{
		this->CameraTargetVectorLength = this->MinTargetDistance;
	}
	else if (this->CameraTargetVectorLength > this->MaxTargetDistance)
	{
		this->CameraTargetVectorLength = this->MaxTargetDistance;
	}
}