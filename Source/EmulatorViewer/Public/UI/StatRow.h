#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatRow.generated.h"

UCLASS()
class EMULATORVIEWER_API UStatRow : public UUserWidget
{
	GENERATED_BODY()

public:

	class UHorizontalBox* HorizontalBox;

	class UTextBlock* StatDescription;

	class UTextBlock* Value;

protected:

	void NativeConstruct() override;

private:

	void SetToolTip(FText InToolTipText);
};