
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

	this->SideStructL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Left"));
	this->SideStructL->SetupAttachment(this->RootComponent);

	this->SideStructR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Struct Right"));
	this->SideStructR->SetupAttachment(this->RootComponent);

	this->SidePanL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Left"));
	this->SidePanL->SetupAttachment(this->RootComponent);

	this->SidePanR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Side Pan Right"));
	this->SidePanR->SetupAttachment(this->RootComponent);

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

