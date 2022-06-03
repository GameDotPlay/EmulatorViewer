
#include "DynamicStraightConveyor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ADynamicStraightConveyor::ADynamicStraightConveyor()
{
	PrimaryActorTick.bCanEverTick = false;

	this->SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	this->SetRootComponent(this->SceneRoot);

	this->ConveyorTail = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Conveyor Tail"));
	this->ConveyorTail->SetupAttachment(this->RootComponent);

	this->ConveyorBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Conveyor Body"));
	this->ConveyorBody->SetupAttachment(this->RootComponent);
	this->ConveyorBody->ComponentTags.Add(FName(TEXT("PhysicsMesh")));

	this->ConveyorHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Conveyor Head"));
	this->ConveyorHead->SetupAttachment(this->RootComponent);

	this->SideStructTailL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Tail Left"));
	this->SideStructTailL->SetupAttachment(this->RootComponent);

	this->SideStructBodyL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Body Left"));
	this->SideStructBodyL->SetupAttachment(this->RootComponent);

	this->SideStructHeadL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Head Left"));
	this->SideStructHeadL->SetupAttachment(this->RootComponent);

	this->SideStructTailR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Tail Right"));
	this->SideStructTailR->SetupAttachment(this->RootComponent);

	this->SideStructBodyR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Body Right"));
	this->SideStructBodyR->SetupAttachment(this->RootComponent);

	this->SideStructHeadR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Head Right"));
	this->SideStructHeadR->SetupAttachment(this->RootComponent);

	this->SidePanTailL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Tail Left"));
	this->SidePanTailL->SetupAttachment(this->RootComponent);

	this->SidePanBodyL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Body Left"));
	this->SidePanBodyL->SetupAttachment(this->RootComponent);

	this->SidePanHeadL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Head Left"));
	this->SidePanHeadL->SetupAttachment(this->RootComponent);

	this->SidePanTailR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Tail Right"));
	this->SidePanTailR->SetupAttachment(this->RootComponent);

	this->SidePanBodyR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Body Right"));
	this->SidePanBodyR->SetupAttachment(this->RootComponent);

	this->SidePanHeadR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Head Right"));
	this->SidePanHeadR->SetupAttachment(this->RootComponent);

	this->TailSnapPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Tail Snap Point"));
	this->TailSnapPoint->SetupAttachment(this->ConveyorTail);

	this->HeadSnapPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Head Snap Point"));
	this->HeadSnapPoint->SetupAttachment(this->ConveyorHead);

	this->ItemSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Point"));
	this->ItemSpawnPoint->SetupAttachment(this->RootComponent);
}

void ADynamicStraightConveyor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADynamicStraightConveyor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}