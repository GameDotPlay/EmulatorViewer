

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

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConveyorTail = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConveyorBody = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ConveyorHead = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructTailL = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructBodyL = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructHeadL = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructTailR = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructBodyR = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SideStructHeadR = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanTailL = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanBodyL = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanHeadL = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanTailR = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanBodyR = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SidePanHeadR = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* TailSnapPoint = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HeadSnapPoint = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ItemSpawnPoint = nullptr;
};
