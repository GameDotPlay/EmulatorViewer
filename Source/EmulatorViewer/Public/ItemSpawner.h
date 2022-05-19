#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class EMULATORVIEWER_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	UStaticMeshComponent* VisibleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float BaseScaleModifier = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float ScaleModifier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float SpawnRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float StartDelay = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	bool bRandomizeScale = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float MaxScaleModifier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	TArray<TSubclassOf<class AItem>> Items;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	struct FTimerHandle SpawnTimerHandle;

	void SpawnItem();

	void InitializeTimer();
};