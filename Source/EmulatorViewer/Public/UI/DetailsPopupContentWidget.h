#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetailsPopupContentWidget.generated.h"

class UCheckBox;
class UVerticalBox;
class UEditableTextBox;
class UFloatInputSettingWidget;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UCheckBox* AddCheckBoxRow(bool InitialCheckedState, bool bEnabled, const FText& InDescription, const FText& InToolTipText = FText::GetEmpty());

	UFloatInputSettingWidget* AddFloatInputRow(const float InitialValue, bool bEnabled, const FText& InDescription, const FText& InToolTipText = FText::GetEmpty());

protected:

	virtual void NativeConstruct() override;

private:
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* BaseVerticalBox;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CheckBoxSettingClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> FloatInputSettingClass;

	TArray<UUserWidget*> Rows;
};
