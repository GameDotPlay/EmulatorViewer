#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PopulateDetailsInterface.h"
#include "ItemSpawner.generated.h"

UCLASS()
class EMULATORVIEWER_API AItemSpawner : public AActor, public IPopulateDetailsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

	virtual void DetailsPopupInteract(class UDetailsPopupContentWidget* ContentWidget) override;

	void KillAllOwnedItems();

	void SetRatePph(float Pph);

	void SetRateHz(float Hz);

	void Enable();

	void Disable();

	float GetRatePph() const { return (1.f / this->SpawnTimerInterval) * 60.f * 60.f; }

	float GetRateHz() const { return 1.f / this->SpawnTimerInterval; }

	int32 GetNumberOfSpawnedItems() const { return this->NumberOfSpawnedItems; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	UStaticMeshComponent* VisibleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float BaseScaleModifier = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float SpawnTimerInterval = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float StartDelay = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	bool bRandomizeScale = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float MinScaleModifier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner")
	float MaxScaleModifier = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AItem>> Items;

	struct FTimerHandle SpawnTimerHandle;

	int32 NumberOfSpawnedItems = 0.f;

	TArray<AItem*> OwnedItems;

	bool bUsingGlobalSettings = true;

	void SpawnItem();

	void InitializeTimer();

	UFUNCTION()
	void EnabledChanged(bool bIsChecked);
};