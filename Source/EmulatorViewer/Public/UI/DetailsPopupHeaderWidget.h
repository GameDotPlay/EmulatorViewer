

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetailsPopupHeaderWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupHeaderWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UDetailsPopupHeaderWidget(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void NativeConstruct() override;

private:

	class USizeBox* Parent = nullptr;

	class UBorder* HeaderBorder = nullptr;

	class UHorizontalBox* HorizontalBox = nullptr;

	class UTextBlock* HeaderText = nullptr;

	class USizeBox* ButtonSizer = nullptr;

	class UButton* CloseButton = nullptr;

	class UTextBlock* CloseButtonText = nullptr;

	void InitializeSettings();

	void InitializeCloseButtonText();

	void InitializeCloseButton();

	void InitializeButtonSizer();

	void InitializeHeaderText();

	void InitializeHorizontalBox();

	void InitializeHeaderBorder();

	void InitializeParent();

	int32 CloseButtonTextFontSize = 8;

	int32 HeaderTextFontSize = 12;

	float ParentBoxMinWidth = 200;

	float ParentBoxMinHeight = 35;

	float ParentBoxMaxHeight = 35;

	FText CloseButtonTextString = FText::FromString("X");

	float CloseButtonSize = 20.f;
};
