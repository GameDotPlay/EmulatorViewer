
#include "InteractableHighlighting.h"

// Sets default values for this component's properties
UInteractableHighlighting::UInteractableHighlighting()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInteractableHighlighting::BeginPlay()
{
	Super::BeginPlay();

	this->Owner = GetOwner();
	check(this->Owner);

	this->Owner->OnBeginCursorOver.AddDynamic(this, &UInteractableHighlighting::OnMouseEnter);
	this->Owner->OnEndCursorOver.AddDynamic(this, &UInteractableHighlighting::OnMouseExit);

	this->Owner->GetComponents<UStaticMeshComponent>(MeshComponentReferences, true);
}

void UInteractableHighlighting::OnMouseEnter(AActor* TouchedActor)
{
	this->SetInteractedActive();
}

void UInteractableHighlighting::OnMouseExit(AActor* TouchedActor)
{
	this->SetInteractedDisabled();
}

void UInteractableHighlighting::SetInteractedActive()
{
	for (int i = 0; i < this->MeshComponentReferences.Num(); i++)
	{
		this->MeshComponentReferences[i]->SetScalarParameterValueOnMaterials(FName("Interact"), 1.f);
	}
}

void UInteractableHighlighting::SetInteractedDisabled()
{
	for (int i = 0; i < this->MeshComponentReferences.Num(); i++)
	{
		this->MeshComponentReferences[i]->SetScalarParameterValueOnMaterials(FName("Interact"), 0.f);
	}
}
