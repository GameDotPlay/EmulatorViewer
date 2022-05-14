

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableHighlighting.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMULATORVIEWER_API UInteractableHighlighting : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableHighlighting();

	UFUNCTION(BlueprintCallable)
	void OnMouseEnter(AActor* TouchedActor);

	UFUNCTION(BlueprintCallable)
	void OnMouseExit(AActor* TouchedActor);

	void SetSelectedActive();

	void SetSelectedDisabled();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	AActor* Owner = nullptr;

	TArray<UStaticMeshComponent*> MeshComponentReferences;

	bool bSelected = false;

	void SetInteractedActive();

	void SetInteractedDisabled();
};
