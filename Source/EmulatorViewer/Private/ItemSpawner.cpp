
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

	this->InitializeTimer();
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
			GetWorldTimerManager().SetTimer(this->SpawnTimerHandle, this, &AItemSpawner::SpawnItem, this->SpawnRate, true, this->StartDelay);
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

		FTransform Transform;
		Transform.SetLocation(this->GetActorLocation());
		Transform.SetRotation(FRotator::ZeroRotator.Quaternion());

		if (this->bRandomizeScale)
		{
			this->ScaleModifier = FMath::RandRange(this->ScaleModifier, this->MaxScaleModifier);
		}
		
		Transform.SetScale3D(FVector(this->BaseScaleModifier * this->ScaleModifier));

		FActorSpawnParameters SpawnParameters;
		AItem* ItemSpawned = GetWorld()->SpawnActor<AItem>(Item, Transform, SpawnParameters);
	}
}