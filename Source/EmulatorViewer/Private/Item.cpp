/*****************************************************************//**
 * @file   Item.cpp
 * @brief  Implementation file for Item.
 * 
 * @author erich.smith
 * @date   July 31, 2023
 *  *********************************************************************/
#include "Item.h"

/** The default constructor. */
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	this->ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	this->SetRootComponent(this->ItemMesh);
}