/*****************************************************************//**
 * @file   DynamicStraightConveyor.h
 * @brief  Class file for DynamicStraightConveyor.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicStraightConveyor.generated.h"

/** Class for a dynamic straight conveyor that can be created and its parameters modified by the user. */
UCLASS()
class EMULATORVIEWER_API ADynamicStraightConveyor : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	 * The default constructor.
	 */
	ADynamicStraightConveyor();

private:

	/** Used as the root component for transform hierarchy. Has no rendered component. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot = nullptr;

	/** The entrance end piece for the conveyor. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConveyorTail = nullptr;

	/** The physical surface that conveys physics items. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConveyorBody = nullptr;

	/** The exit end piece for the conveyor. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConveyorHead = nullptr;

	/** Mesh that covers the hollow left side of a conveyor belt tail mesh. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructTailL = nullptr;

	/** Mesh that covers the hollow left side of a conveyor belt PhysicsMesh. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructBodyL = nullptr;

	/**  Mesh that covers the hollow left side of a conveyor belt head mesh. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructHeadL = nullptr;

	/**  Mesh that covers the hollow right side of a conveyor belt tail mesh. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructTailR = nullptr;

	/** Mesh that covers the hollow right side of a conveyor belt PhysicsMesh. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructBodyR = nullptr;

	/** Mesh that covers the hollow right side of a conveyor belt head mesh. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructHeadR = nullptr;

	/** Optional side wall for a conveyor tail mesh that keeps items from leaving the surface. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanTailL = nullptr;

	/** Optional side wall for a conveyor that keeps items from leaving the surface. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanBodyL = nullptr;

	/** Optional side wall for a conveyor head mesh that keeps items from leaving the surface. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanHeadL = nullptr;

	/** Optional side wall for a conveyor tail mesh that keeps items from leaving the surface. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanTailR = nullptr;

	/** Optional side wall for a conveyor that keeps items from leaving the surface. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanBodyR = nullptr;

	/** Optional side wall for a conveyor head mesh that keeps items from leaving the surface. Set mesh in editor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanHeadR = nullptr;

	/** The point at the entrance of a conveyor that can "snap" to other components in the scene during editing. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* TailSnapPoint = nullptr;

	/** The point at the exit of a conveyor that can "snap" to other components in the scene during editing. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeadSnapPoint = nullptr;

	/** Customizable location the user can set for items to spawn over this conveyor. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ItemSpawnPoint = nullptr;
};
