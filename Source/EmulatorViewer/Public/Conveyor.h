/*****************************************************************//**
 * @file   Conveyor.h
 * @brief  Class file for Conveyor.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Conveyor.generated.h"

/** Represents a conveyor in the world. */
UCLASS()
class EMULATORVIEWER_API AConveyor : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	 * The default constructor.
	 */
	AConveyor();

private:

	/** Used as the root component for transform hierarchy. Has no rendered component. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot = nullptr;
	
	/** The physical surface that conveys physics items. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PhysicsMesh = nullptr;

	/** Mesh that covers the hollow right side of a conveyor belt PhysicsMesh. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructR = nullptr;

	/** Mesh that covers the hollow left side of a conveyor belt PhysicsMesh.. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructL = nullptr;

	/** Optional side wall for a conveyor that keeps items from leaving the surface. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanR = nullptr;

	/** Optional side wall for a conveyor that keeps items from leaving the surface. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanL = nullptr;
};
