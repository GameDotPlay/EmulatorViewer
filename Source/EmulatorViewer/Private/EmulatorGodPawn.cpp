/*****************************************************************//**
 * @file   EmulatorGodPawn.cpp
 * @brief  Implementation file for EmulatorGodPawn.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#include "EmulatorGodPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EmulatorPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InteractableHighlighting.h"
#include "PopulateDetailsInterface.h"
#include "UI/DetailsPopupWidget.h"

/**
 * The default constructor.
 * Initializes any default values.
 */
AEmulatorGodPawn::AEmulatorGodPawn()
{
	this->PhysicsHandle = Super::CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");

	PhysicsHandle->LinearDamping = 30000.f;
	PhysicsHandle->LinearStiffness = 100000.f;
	PhysicsHandle->AngularDamping = 50000.f;
	PhysicsHandle->AngularStiffness = 200000.f;
	PhysicsHandle->InterpolationSpeed = 17.f;
}

/**
 * Called once per frame.
 * @param DeltaTime The time in ms since the last frame.
 */
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

/**
 * The F key has been pressed.
 * Snap the focal point to the currently selected item.
 */
void AEmulatorGodPawn::KeyboardF()
{
	this->FocusView();
}

/**
 * Test for a valid physics object under the cursor and grab it.
 * @param HitResult The FHitResult returned from the object under the cursor.
 */
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

/**
 * Release the currently held physics object.
 */
void AEmulatorGodPawn::ReleasePhysicsObject()
{
	if (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent))
	{
		this->PhysicsHandle->ReleaseComponent();
		this->PlayerController->CurrentMouseCursor = EMouseCursor::GrabHand;
	}
}

/**
 * The END key has been pressed.
 * Reset the focal point down to floor level.
 */
void AEmulatorGodPawn::KeyboardEND()
{
	Super::SetActorLocation(FVector(Super::GetActorLocation().X, Super::GetActorLocation().Y, this->FloorZ + this->FloorZOffset));
}

/**
 * The ESC key has been pressed.
 * Pause the sim and open the pause menu.
 */
void AEmulatorGodPawn::KeyboardESC()
{
	this->PlayerController->TogglePause();
}

/**
 * The SPACE key has been pressed.
 * Either grab or release a physics object under the cursor.
 */
void AEmulatorGodPawn::KeyboardSPACE()
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

/**
 * The mouse wheel has been scrolled.
 * Either zoom the camera or move the currently held physics item further away/closer to the camera.
 * @param Value The value the mouse wheel has moved.
 */
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

/**
 * The left mouse button has been clicked.
 * Test for a valid object under the cursor and set it as the currently selected object.
 */
void AEmulatorGodPawn::LeftMouseClick()
{
	FHitResult HitResult;
	this->PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	if (this->CurrentSelection == HitActor || !IsValid(HitActor))
	{
		return;
	}

	if (IsValid(this->CurrentSelection))
	{
		// Turn off current selection highlighting.
		UInteractableHighlighting* HighlightComponent = this->GetHighlightingComponent(this->CurrentSelection);
		if (IsValid(HighlightComponent))
		{
			HighlightComponent->SetSelectedDisabled();
		}
	}

	UInteractableHighlighting* HighlightComponent = this->GetHighlightingComponent(HitActor);
	if (IsValid(HighlightComponent))
	{
		HighlightComponent->SetSelectedActive();
		this->CurrentSelection = HitActor;
	}
}

/**
 * The right mouse button has been clicked.
 * Open the details pop up if the object implements it.
 */
void AEmulatorGodPawn::RightMouseClick()
{
	FHitResult HitResult;
	this->PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	if (IsValid(HitActor))
	{
		IPopulateDetailsInterface* ActorInterface = Cast<IPopulateDetailsInterface>(HitActor);
		if (ActorInterface)
		{
			ActorInterface->DetailsPopupInteract(this->PlayerController->GetMainHUD());
		}
	}
}

/**
 * Get the InteractableHighlighting component of the actor that was clicked.
 * @param Actor The Actor that was clicked.
 * @return The InteractableHighlighting component of the Actor that was clicked. If it exists.
 */
UInteractableHighlighting* AEmulatorGodPawn::GetHighlightingComponent(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return nullptr;
	}

	UActorComponent* Component = Actor->GetComponentByClass(UInteractableHighlighting::StaticClass());
	UInteractableHighlighting* HighlightComponent = Cast<UInteractableHighlighting>(Component);

	if (!IsValid(HighlightComponent))
	{
		return nullptr;
	}
	else
	{
		return HighlightComponent;
	}
}

/**
 * Is a physics object currently being held?
 */
bool AEmulatorGodPawn::CurrentlyHoldingObject()
{
	return (IsValid(this->PhysicsHandle) && IsValid(this->PhysicsHandle->GrabbedComponent));
}

/**
 * Snap the focal point to the currently selected object, if valid.
 */
void AEmulatorGodPawn::FocusView()
{
	if (IsValid(this->CurrentSelection))
	{
		FVector SelectionExtents;
		FVector SelectionOrigin;
		this->CurrentSelection->GetActorBounds(true, SelectionOrigin, SelectionExtents, true);
		Super::SetActorLocation(SelectionOrigin);
	}
}

/**
 * Zoom the camera closer or further away from the focal point.
 * @param Value
 */
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

/**
 * Move the currently held physics object further away or closer to the camera.
 * @param Value The value to move the object.
 */
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
