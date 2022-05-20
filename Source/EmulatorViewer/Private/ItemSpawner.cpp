
#include "ItemSpawner.h"
#include "Item.h"
#include "TimerManager.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->VisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));
	this->SetRootComponent(this->VisibleMesh);
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (this->bEnabled)
	{
		this->InitializeTimer();
	}
}

void AItemSpawner::InitializeTimer()
{
	if (!GetWorld())
	{
		return;
	}

	if (GetWorld()->bShouldSimulatePhysics)
	{
		if (this->bEnabled)
		{
			GetWorldTimerManager().SetTimer(this->SpawnTimerHandle, this, &AItemSpawner::SpawnItem, this->SpawnTimerInterval, true, this->StartDelay);
			return;
		}
	}

	GetWorldTimerManager().ClearTimer(this->SpawnTimerHandle);
}

void AItemSpawner::SpawnItem()
{
	if (!this->bEnabled)
	{
		return;
	}

	if (this->Items.Num() > 0)
	{
		int32 index = FMath::RandRange(0, this->Items.Num() - 1);
		TSubclassOf<AItem> Item = this->Items[index];

		FTransform Transform = this->GetActorTransform();

		float ScaleModifier = 1.f;
		if (this->bRandomizeScale)
		{
			ScaleModifier = FMath::RandRange(this->MinScaleModifier, this->MaxScaleModifier);
		}
		
		Transform.SetScale3D(FVector(this->BaseScaleModifier * ScaleModifier));

		FActorSpawnParameters SpawnParameters;
		AItem* ItemSpawned = GetWorld()->SpawnActor<AItem>(Item, Transform, SpawnParameters);

		if (ItemSpawned)
		{
			this->NumberOfSpawnedItems++;
			this->OwnedItems.Emplace(ItemSpawned);
		}
	}
}

void AItemSpawner::KillAllOwnedItems()
{
	if (this->OwnedItems.Num() > 0)
	{
		for (int i = 0; i < this->OwnedItems.Num(); i++)
		{
			if (this->OwnedItems[i])
			{
				this->OwnedItems[i]->Destroy(false, false);
			}
			else
			{
				this->OwnedItems.RemoveAt(i);
			}
		}

		this->NumberOfSpawnedItems = 0;
		this->OwnedItems.Empty();
	}
}

void AItemSpawner::SetRatePph(float Pph)
{
	this->SpawnTimerInterval = 1.f / (Pph / 60.f / 60.f);
	this->InitializeTimer();
}

void AItemSpawner::SetRateHz(float Hz)
{
	this->SpawnTimerInterval = 1.f / Hz;
	this->InitializeTimer();
}

void AItemSpawner::Enable()
{
	this->bEnabled = true;
	this->InitializeTimer();
}

void AItemSpawner::Disable()
{
	this->bEnabled = false;
	if (this->SpawnTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(this->SpawnTimerHandle);
	}
}

void AItemSpawner::DetailsPopupInteract(class UUserWidget* DetailsWidget)
{

}