/*****************************************************************//**
 * @file   EmulatorGodPawn.h
 * @brief  Class file for EmulatorGodPawn.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInterface.h"
#include "FloatingPawnBase.h"
#include "EmulatorGodPawn.generated.h"

class UInteractableHighlighting;
class UPhysicsHandleComponent;

/** Class for a "god mode" pawn allowing the player to move freely in the scene. */
UCLASS()
class EMULATORVIEWER_API AEmulatorGodPawn : public AFloatingPawnBase
{
	GENERATED_BODY()

public:

	/**
	 * The default constructor.
	 */
	AEmulatorGodPawn();

	/**
	 * Sets the focal point of the camera to the position of the current selection. If the current selection is a valid object.
	 */
	void KeyboardF() override;

	/**
	 * Resets the focal point of the camera down to floor level.
	 */
	void KeyboardEND() override;

	/**
	 * Pauses the sim and opens the pause menu.
	 */
	void KeyboardESC() override;

	/**
	 * Grabs/releases a physics object under the cursor.
	 */
	void KeyboardSPACE() override;

	/**
	 * Zooms the camera in/out based on the value given.
	 * If in Interact mode, moves the held item closer or further from the camera based on the value given.
	 * @param Value The value to zoom, or move the item by.
	 */
	void MouseWheelAxis(float Value) override;

	/**
	 * Sets the current selection to the object under the cursor.
	 */
	virtual void LeftMouseClick() override;

	/**
	 * Opens the details pop up of an object if that object implements it.
	 */
	virtual void RightMouseClick() override;

	/**
	 * Is a physics object currently being held?
	 */
	bool CurrentlyHoldingObject() override;

protected:

	/**
	 * Called once per frame.
	 * @param DeltaTime The time in ms since the last frame.
	 */
	virtual void Tick(float DeltaTime) override;

private:

	/** The PhysicsHandleComponent that allows the player to grab physics items in the scene. */
	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	/** The vector from the camera to the focal point. */
	FVector CameraTargetVector;

	/** The length of the CameraTargetVector. */
	float CameraTargetVectorLength;

	/** The minimum distance in cm the camera can be from the focal point. */
	float MinTargetDistance = 300.f;

	/** The maximum distance in cm the camera can be from the focal point. */
	float MaxTargetDistance = 1000.f;

	/** The multiplier of the mouse wheel adjustments. Higher number is more sensitive. */
	float DistanceAdjustSensitivity = 1000.f;

	/** The currently selected object. */
	AActor* CurrentSelection = nullptr;

	/**
	 * Snaps the focal point of the camera to the currently selected object.
	 */
	void FocusView();

	/**
	 * Zooms the camera into or away from the focal point.
	 * @param Value The value to zoom the camera by.
	 */
	void Zoom(float Value);

	/**
	 * Move the currently held physics object further away/closer to the camera.
	 * @param Value The value to move the object by.
	 */
	void PhysicsObjectDistanceAdjust(float Value);

	/**
	 * Grabs a physics item under the cursor.
	 * @param HitResult
	 */
	void GrabPhysicsObject(FHitResult HitResult);

	/**
	 * Releases the currently held physics item.
	 */
	void ReleasePhysicsObject();

	/**
	 * Get the UInteractableHighlighting component of the object that was clicked.
	 * @param Actor The Actor that was clicked.
	 * @return The UInteractableHighlighting component of the object that was clicked. If it exists.
	 */
	UInteractableHighlighting* GetHighlightingComponent(AActor* Actor);
};
