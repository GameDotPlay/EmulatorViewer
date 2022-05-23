#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetailsPopupContentWidget.generated.h"

class UCheckBox;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddRow(TSubclassOf<UUserWidget> UserWidget);

	UCheckBox* AddCheckBoxRow(ECheckBoxState InitialCheckedState, bool bEnabled, const FText& Description, const FText& ToolTip = FText::GetEmpty());

protected:

	virtual void NativeConstruct() override;

private:
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* BaseVerticalBox;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CheckBoxSettingClass;

	TArray<UUserWidget*> Rows;
};
