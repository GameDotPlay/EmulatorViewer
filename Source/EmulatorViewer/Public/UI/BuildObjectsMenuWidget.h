
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildObjectsMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UBuildObjectsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UButton* GetCreateStraightButton() { return this->CreateStraightButton; }

protected:

private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* CreateStraightButton = nullptr;
	
};
