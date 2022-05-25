#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	this->ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	this->SetRootComponent(this->ItemMesh);
}