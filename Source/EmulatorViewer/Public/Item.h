// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class AItemSpawner;

UCLASS()
class EMULATORVIEWER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

	void SetParent(const AItemSpawner* InParent) { this->Parent = InParent; }

	const AItemSpawner* GetParent() const { return this->Parent; }

protected:

private:

	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	const AItemSpawner* Parent = nullptr;
};
