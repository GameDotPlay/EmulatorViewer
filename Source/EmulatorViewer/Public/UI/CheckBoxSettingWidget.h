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

	ECheckBoxState GetCheckBoxValue();

	void SetLabelText(FText LabelText);

	void SetSettingToolTip(FText InToolTipText);

protected:

	void NativeConstruct() override;

	UPROPERTY( meta = (BindWidget))
	class UHorizontalBox* HorizontalContainer;

	UPROPERTY( meta = (BindWidget))
	class UCheckBox* CheckBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SettingLabel;
};