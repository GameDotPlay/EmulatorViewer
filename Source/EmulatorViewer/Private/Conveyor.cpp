#include "Conveyor.h"

// Sets default values
AConveyor::AConveyor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->PhysicsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PhysicsMesh"));
	this->SetRootComponent(this->PhysicsMesh);

	this->SideStructR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideStructR"));
	this->SideStructR->SetupAttachment(this->RootComponent);

	this->SideStructL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SideStructL"));
	this->SideStructL->SetupAttachment(this->RootComponent);

	this->SidePanL24in = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SidePanL24in"));
	this->SidePanL24in->SetupAttachment(this->RootComponent);

	this->SidePanR24in = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SidePanR24in"));
	this->SidePanR24in->SetupAttachment(this->RootComponent);
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