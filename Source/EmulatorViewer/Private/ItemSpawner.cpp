
#include "ItemSpawner.h"
#include "Item.h"
#include "TimerManager.h"
#include "UI/DetailsPopupContentWidget.h"
#include "Components/CheckBox.h"
#include "UI/EmulatorViewerHUD.h"
#include "UI/FloatInputSettingWidget.h"
#include "UI/DetailsPopupWidget.h"

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
	if (GetWorld() && GetWorld()->bShouldSimulatePhysics)
	{
		if (this->bEnabled)
		{
			GetWorldTimerManager().ClearTimer(this->SpawnTimerHandle);
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
			ItemSpawned->SetSpawner(this);
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

void AItemSpawner::DetailsPopupInteract(AEmulatorViewerHUD* MainHUD)
{
	UDetailsPopupWidget* DetailsPopup = Cast<UDetailsPopupWidget>(CreateWidget(GetWorld(), this->DetailsPopupClass));
	UDetailsPopupContentWidget* ContentWidget = DetailsPopup->GetContentWidget();
	DetailsPopup->SetHeaderText(FText::FromString(this->GetActorNameOrLabel()));

	UCheckBox* EnabledCheckBox = ContentWidget->AddCheckBoxRow(this->bEnabled, !this->bUsingGlobalSettings, FText::FromString(TEXT("Enabled")), FText::FromString(TEXT("Enable or disable this item spawner.")));
	if (IsValid(EnabledCheckBox))
	{
		EnabledCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &AItemSpawner::EnabledChanged);
	}

	UCheckBox* RandomizeScaleCheckBox = ContentWidget->AddCheckBoxRow(this->bRandomizeScale, !this->bUsingGlobalSettings, FText::FromString(TEXT("Randomize Item Scale")), FText::FromString(TEXT("Randomize the scale of spawned items.")));
	if (IsValid(RandomizeScaleCheckBox))
	{
		RandomizeScaleCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &AItemSpawner::RandomizeScaleChanged);
	}

	UFloatInputSettingWidget* BaseScaleModiferTextBox = nullptr;
	BaseScaleModiferTextBox = ContentWidget->AddFloatInputRow(this->BaseScaleModifier, !this->bUsingGlobalSettings, FText::FromString(TEXT("Base scale modifier")), FText::FromString(TEXT("All items spawned will have their scales in all three axes multiplied by this value.")));
	if (BaseScaleModiferTextBox)
	{
		BaseScaleModiferTextBox->OnTextInputValidatedDelegate.AddUniqueDynamic(this, &AItemSpawner::BaseScaleModifierChanged);
	}

	UFloatInputSettingWidget* MinScaleModiferTextBox = nullptr;
	MinScaleModiferTextBox = ContentWidget->AddFloatInputRow(this->MinScaleModifier, !this->bUsingGlobalSettings, FText::FromString(TEXT("Minimum scale modifier")), FText::FromString(TEXT("If randomize scale is enabled, this is the minimum value the item scale will be modified by.")));
	if (MinScaleModiferTextBox)
	{
		MinScaleModiferTextBox->OnTextInputValidatedDelegate.AddUniqueDynamic(this, &AItemSpawner::MinScaleModifierChanged);
	}

	UFloatInputSettingWidget* MaxScaleModiferTextBox = nullptr;
	MaxScaleModiferTextBox = ContentWidget->AddFloatInputRow(this->MaxScaleModifier, !this->bUsingGlobalSettings, FText::FromString(TEXT("Maximum scale modifier")), FText::FromString(TEXT("If randomize scale is enabled, this is the maximum value the item scale will be modified by.")));
	if (MaxScaleModiferTextBox)
	{
		MaxScaleModiferTextBox->OnTextInputValidatedDelegate.AddUniqueDynamic(this, &AItemSpawner::MaxScaleModifierChanged);
	}

	UFloatInputSettingWidget* StartDelayTextBox = nullptr;
	StartDelayTextBox = ContentWidget->AddFloatInputRow(this->StartDelay, !this->bUsingGlobalSettings, FText::FromString(TEXT("Start delay")), FText::FromString(TEXT("The time in seconds to wait after enabled to begin spawning items.")));
	if (StartDelayTextBox)
	{
		StartDelayTextBox->OnTextInputValidatedDelegate.AddUniqueDynamic(this, &AItemSpawner::StartDelayChanged);
	}

	UFloatInputSettingWidget* SpawnTimerIntervalTextBox = nullptr;
	SpawnTimerIntervalTextBox = ContentWidget->AddFloatInputRow(this->SpawnTimerInterval, !this->bUsingGlobalSettings, FText::FromString(TEXT("Spawn timer interval")), FText::FromString(TEXT("Interval in seconds between spawning items.")));
	if (SpawnTimerIntervalTextBox)
	{
		SpawnTimerIntervalTextBox->OnTextInputValidatedDelegate.AddUniqueDynamic(this, &AItemSpawner::SpawnTimerIntervalChanged);
	}

	if (IsValid(MainHUD))
	{
		MainHUD->AddDetailsPopup(DetailsPopup);
	}
}

void AItemSpawner::EnabledChanged(bool bIsChecked)
{
	(bIsChecked) ? this->Enable() : this->Disable();
}

void AItemSpawner::RandomizeScaleChanged(bool bIsChecked)
{
	this->bRandomizeScale = bIsChecked;
}

void AItemSpawner::BaseScaleModifierChanged(float Value)
{
	this->BaseScaleModifier = Value;
}

void AItemSpawner::MinScaleModifierChanged(float Value)
{
	this->MinScaleModifier = Value;
}

void AItemSpawner::MaxScaleModifierChanged(float Value)
{
	this->MaxScaleModifier = Value;
}

void AItemSpawner::StartDelayChanged(float Value)
{
	this->StartDelay = Value;
}

void AItemSpawner::SpawnTimerIntervalChanged(float Value)
{
	this->SpawnTimerInterval = Value;
	this->InitializeTimer();
}
