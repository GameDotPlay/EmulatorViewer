#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CheckBoxSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UCheckBoxSettingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetToolTip(FText InToolTipText);

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SettingLabel;

protected:

	void NativeConstruct() override;
};