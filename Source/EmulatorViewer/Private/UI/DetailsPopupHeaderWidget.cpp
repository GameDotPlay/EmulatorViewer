
#include "UI/DetailsPopupHeaderWidget.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Fonts/SlateFontInfo.h"

void UDetailsPopupHeaderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->CloseButton->AddChild(this->CloseButtonText);
	this->ButtonSizer->AddChild(this->CloseButton);
	this->HorizontalBox->AddChild(this->HeaderText);
	this->HorizontalBox->AddChild(this->ButtonSizer);
	this->HeaderBorder->AddChild(this->HorizontalBox);
	this->Parent->AddChild(this->HeaderBorder);

	this->InitializeSettings();
}

void UDetailsPopupHeaderWidget::InitializeSettings()
{
	UButtonSlot* ParentButtonSlot = Cast<UButtonSlot>(this->CloseButtonText->Slot);
	ParentButtonSlot->SetPadding(FMargin());
	ParentButtonSlot->SetHorizontalAlignment(HAlign_Center);
	ParentButtonSlot->SetVerticalAlignment(VAlign_Center);
	this->CloseButtonText->Slot = ParentButtonSlot;

	this->CloseButtonText->SetText(FText::FromString("X"));
	//FSlateFontInfo FontInfo;
	//FontInfo.Size = 8;
	//this->CloseButtonText->SetFont(FontInfo);

	this->CloseButtonText->SetJustification(ETextJustify::Center);
	this->CloseButtonText->SetIsEnabled(true);
	this->CloseButtonText->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->CloseButtonText->SetCursor(EMouseCursor::Default);
}