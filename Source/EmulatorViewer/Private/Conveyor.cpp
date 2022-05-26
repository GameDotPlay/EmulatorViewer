
#include "Conveyor.h"

// Sets default values
AConveyor::AConveyor()
{
	PrimaryActorTick.bCanEverTick = true;

	this->PhysicsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhysicsMesh"));
	this->SetRootComponent(this->PhysicsMesh);

	this->SideStructR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideStructR"));
	this->SideStructR->SetupAttachment(this->RootComponent);

	this->SideStructL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideStructL"));
	this->SideStructL->SetupAttachment(this->RootComponent);

	this->SidePanL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SidePanL"));
	this->SidePanL->SetupAttachment(this->RootComponent);

	this->SidePanR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SidePanR"));
	this->SidePanR->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AConveyor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AConveyor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}