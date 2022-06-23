#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PopulateDetailsInterface.h"
#include "ItemSpawner.generated.h"

class UUserWidget;
class AEmulatorViewerHUD;

UCLASS()
class EMULATORVIEWER_API AItemSpawner : public AActor, public IPopulateDetailsInterface
{
	GENERATED_BODY()
	
public:	

	AItemSpawner();

	virtual void DetailsPopupInteract(AEmulatorViewerHUD* MainHUD) override;

	void KillAllOwnedItems();

	void SetRatePph(float Pph);

	void SetRateHz(float Hz);

	void Enable();

	void Disable();

	float GetRatePph() const { return (1.f / this->SpawnTimerInterval) * 60.f * 60.f; }

	float GetRateHz() const { return 1.f / this->SpawnTimerInterval; }

	int32 GetNumberOfSpawnedItems() const { return this->NumberOfSpawnedItems; }

	int32 GetNumberOfItemsInWorld() const { return this->OwnedItems.Num(); }

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AItem>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* VisibleMesh;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DetailsPopupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	float BaseScaleModifier = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	float SpawnTimerInterval = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	float StartDelay = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	bool bRandomizeScale = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	float MinScaleModifier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSpawner", meta = (AllowPrivateAccess = "true"))
	float MaxScaleModifier = 1.f;

	struct FTimerHandle SpawnTimerHandle;

	int32 NumberOfSpawnedItems = 0;

	TArray<AItem*> OwnedItems;

	bool bUsingGlobalSettings = false;

	void SpawnItem();

	void InitializeTimer();

	UFUNCTION()
	void EnabledChanged(bool bIsChecked);

	UFUNCTION()
	void RandomizeScaleChanged(bool bIsChecked);

	UFUNCTION()
	void BaseScaleModifierChanged(float Value);

	UFUNCTION()
	void MinScaleModifierChanged(float Value);

	UFUNCTION()
	void MaxScaleModifierChanged(float Value);

	UFUNCTION()
	void StartDelayChanged(float Value);

	UFUNCTION()
	void SpawnTimerIntervalChanged(float Value);
};