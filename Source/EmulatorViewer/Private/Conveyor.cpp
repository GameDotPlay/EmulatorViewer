/*****************************************************************//**
 * @file   Conveyor.cpp
 * @brief  Implementation file for Conveyor.
 * 
 * @author Erich Smith
 * @date   August 01, 2023
 *  *********************************************************************/
#include "Conveyor.h"

/**
 * The default constructor.
 * Initializes all mesh references and sets up the transform hierarchy.
 */
AConveyor::AConveyor()
{
	PrimaryActorTick.bCanEverTick = false;

	this->SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
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
