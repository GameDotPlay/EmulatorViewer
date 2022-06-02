

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicStraightConveyor.generated.h"

UCLASS()
class EMULATORVIEWER_API ADynamicStraightConveyor : public AActor
{
	GENERATED_BODY()
	
public:	

	ADynamicStraightConveyor();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UStaticMeshComponent* ConveyorTail = nullptr;

	UStaticMeshComponent* ConveyorBody = nullptr;

	UStaticMeshComponent* ConveyorHead = nullptr;

	UStaticMeshComponent* SideStructL = nullptr;

	UStaticMeshComponent* SideStructR = nullptr;

	UStaticMeshComponent* SidePanL = nullptr;

	UStaticMeshComponent* SidePanR = nullptr;
};
