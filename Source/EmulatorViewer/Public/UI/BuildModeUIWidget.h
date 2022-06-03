
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildObjectsMenuWidget.h"
#include "BuildModeUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UBuildModeUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UBuildObjectsMenuWidget* GetBuildObjectsMenu() { return Cast<UBuildObjectsMenuWidget>(this->BuildObjectsMenu); }

protected:

private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUserWidget* BuildObjectsMenu = nullptr;

};