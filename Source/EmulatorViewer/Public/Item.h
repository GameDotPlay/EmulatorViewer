/*****************************************************************//**
 * @file   Item.h
 * @brief  Class file for an Item.
 * 
 * @author erich.smith
 * @date   July 2023
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class AItemSpawner;

/** Represents an item that can be placed in the world and affected by physics. */
UCLASS()
class EMULATORVIEWER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	/** The default constructor. */
	AItem();

	/**
	 * Sets the reference to the AItemSpawner that spawned this item..
	 * @param InSpawner The AItemSpawner that spawned this item.
	 */
	void SetSpawner(const AItemSpawner* InSpawner) { this->Spawner = InSpawner; }

	/** Gets a reference to the AItemSpawner that spawned this item. */
	const AItemSpawner* GetParent() const { return this->Spawner; }

private:

	/** The static mesh component to be set in the editor. */
	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	/** Reference to the AItemSpawner that spawned this item. */
	const AItemSpawner* Spawner = nullptr;
};
