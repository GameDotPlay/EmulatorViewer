
#include "Conveyor.h"

AConveyor::AConveyor()
{
	PrimaryActorTick.bCanEverTick = true;

	this->SceneRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SceneRoot"));
	this->SetRootComponent(this->SceneRoot);

	this->PhysicsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhysicsMesh"));
	this->PhysicsMesh->SetupAttachment(this->RootComponent);
	this->PhysicsMesh->ComponentTags.Add(FName(TEXT("PhysicsMesh")));

	this->SideStructR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideStructR"));
	this->SideStructR->SetupAttachment(this->RootComponent);

	this->SideStructL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideStructL"));
	this->SideStructL->SetupAttachment(this->RootComponent);

	this->SidePanL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SidePanL"));
	this->SidePanL->SetupAttachment(this->RootComponent);

	this->SidePanR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SidePanR"));
	this->SidePanR->SetupAttachment(this->RootComponent);
}

void AConveyor::BeginPlay()
{
	Super::BeginPlay();
}

void AConveyor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}