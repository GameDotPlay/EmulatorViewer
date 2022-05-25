

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;
};
