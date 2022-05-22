
#include "UI/DetailsPopupHeaderWidget.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateTypes.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"


UDetailsPopupHeaderWidget::UDetailsPopupHeaderWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("In Constructor()"));

	/*this->Parent = Cast<USizeBox>(USizeBox::StaticClass());
	this->HeaderBorder = Cast<UBorder>(UBorder::StaticClass());
	this->HorizontalBox = Cast<UHorizontalBox>(UHorizontalBox::StaticClass());
	this->ButtonSizer = Cast<USizeBox>(USizeBox::StaticClass());
	this->CloseButton = Cast<UButton>(UButton::StaticClass());
	this->CloseButtonText = Cast<UTextBlock>(UTextBlock::StaticClass());*/
}

void UDetailsPopupHeaderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("Entered NativeConstruct()"));

	this->Parent = Cast<USizeBox>(CreateWidget(this, USizeBox::StaticClass()));
	this->HeaderBorder = Cast<UBorder>(CreateWidget(this, UBorder::StaticClass()));
	this->HorizontalBox = Cast<UHorizontalBox>(CreateWidget(this, UHorizontalBox::StaticClass()));
	this->ButtonSizer = Cast<USizeBox>(CreateWidget(this, USizeBox::StaticClass()));
	this->CloseButton = Cast<UButton>(CreateWidget(this, UButton::StaticClass()));
	this->CloseButtonText = Cast<UTextBlock>(CreateWidget(this, UTextBlock::StaticClass()));

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
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeSettings()"));

	this->InitializeCloseButtonText();
	this->InitializeCloseButton();
	this->InitializeButtonSizer();
	this->InitializeHeaderText();
	this->InitializeHorizontalBox();
	this->InitializeHeaderBorder();
	this->InitializeParent();
}

void UDetailsPopupHeaderWidget::InitializeCloseButtonText()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeCloseButtonText()"));

	if (!IsValid(this->CloseButtonText))
	{
		UE_LOG(LogTemp, Warning, TEXT("CloseButtonText null."));
		return;
	}

	UButtonSlot* ParentButtonSlot = Cast<UButtonSlot>(this->CloseButtonText->Slot);
	ParentButtonSlot->SetPadding(FMargin());
	ParentButtonSlot->SetHorizontalAlignment(HAlign_Center);
	ParentButtonSlot->SetVerticalAlignment(VAlign_Center);
	this->CloseButtonText->Slot = ParentButtonSlot;

	this->CloseButtonText->SetText(this->CloseButtonTextString);
	FSlateFontInfo FontInfo;
	FontInfo.Size = this->CloseButtonTextFontSize;
	this->CloseButtonText->SetFont(FontInfo);

	this->CloseButtonText->SetJustification(ETextJustify::Center);
	this->CloseButtonText->SetIsEnabled(true);
	this->CloseButtonText->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->CloseButtonText->SetCursor(EMouseCursor::Default);
}

void UDetailsPopupHeaderWidget::InitializeCloseButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeCloseButton()"));

	if (!IsValid(this->CloseButton))
	{
		UE_LOG(LogTemp, Warning, TEXT("CloseButton null."));
		return;
	}

	USizeBoxSlot* ParentSlot = Cast<USizeBoxSlot>(this->CloseButton->Slot);
	ParentSlot->SetPadding(FMargin());
	ParentSlot->SetHorizontalAlignment(HAlign_Fill);
	ParentSlot->SetVerticalAlignment(VAlign_Fill);
	this->CloseButton->Slot = ParentSlot;

	FButtonStyle ButtonStyle = FButtonStyle::GetDefault();
	ButtonStyle.NormalPadding = 0;
	ButtonStyle.PressedPadding = 0;
	this->CloseButton->SetStyle(ButtonStyle);
	this->CloseButton->SetBackgroundColor(FColor::Red);
	this->CloseButton->SetIsEnabled(true);
	this->CloseButton->SetVisibility(ESlateVisibility::Visible);
	this->CloseButton->SetCursor(EMouseCursor::Default);
}

void UDetailsPopupHeaderWidget::InitializeButtonSizer()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeButtonSizer()"));

	if (!IsValid(this->ButtonSizer))
	{
		UE_LOG(LogTemp, Warning, TEXT("ButtonSizer null."));
		return;
	}

	UHorizontalBoxSlot* ParentSlot = Cast<UHorizontalBoxSlot>(this->ButtonSizer->Slot);
	ParentSlot->SetPadding(FMargin(2.f));
	FSlateChildSize ChildSize;
	ChildSize.SizeRule = ESlateSizeRule::Fill;
	ChildSize.Value = 1.f;
	ParentSlot->SetSize(ChildSize);
	ParentSlot->SetHorizontalAlignment(HAlign_Right);
	ParentSlot->SetVerticalAlignment(VAlign_Center);
	this->ButtonSizer->Slot = ParentSlot;

	this->ButtonSizer->SetHeightOverride(this->CloseButtonSize);
	this->ButtonSizer->SetWidthOverride(this->CloseButtonSize);
	this->ButtonSizer->SetIsEnabled(true);
	this->ButtonSizer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	this->ButtonSizer->SetCursor(EMouseCursor::Default);
}

void UDetailsPopupHeaderWidget::InitializeHeaderText()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeHeaderText()"));

	if (!IsValid(this->HeaderText))
	{
		UE_LOG(LogTemp, Warning, TEXT("HeaderText null."));
		return;
	}

	UHorizontalBoxSlot* ParentSlot = Cast<UHorizontalBoxSlot>(this->HeaderText->Slot);
	ParentSlot->SetPadding(FMargin(2.f));
	FSlateChildSize ChildSize;
	ChildSize.SizeRule = ESlateSizeRule::Automatic;
	ParentSlot->SetSize(ChildSize);
	ParentSlot->SetHorizontalAlignment(HAlign_Left);
	ParentSlot->SetVerticalAlignment(VAlign_Center);
	this->HeaderText->Slot = ParentSlot;

	this->HeaderText->SetText(FText::FromString("Placeholder"));
	this->HeaderText->SetColorAndOpacity(FSlateColor(FColor::Black));
	FSlateFontInfo FontInfo;
	FontInfo.Size = this->HeaderTextFontSize;
	this->HeaderText->SetFont(FontInfo);
	this->HeaderText->SetJustification(ETextJustify::Center);
	this->SetIsEnabled(true);
	this->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UDetailsPopupHeaderWidget::InitializeHorizontalBox()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeHorizontalBox()"));

	if (!IsValid(this->HorizontalBox))
	{
		UE_LOG(LogTemp, Warning, TEXT("HorizontalBox null."));
		return;
	}

	UBorderSlot* ParentSlot = Cast<UBorderSlot>(this->HorizontalBox->Slot);
	ParentSlot->SetPadding(FMargin(3.f));
	ParentSlot->SetHorizontalAlignment(HAlign_Fill);
	ParentSlot->SetVerticalAlignment(VAlign_Fill);
	this->HorizontalBox->Slot = ParentSlot;

	this->SetIsEnabled(true);
	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UDetailsPopupHeaderWidget::InitializeHeaderBorder()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeHeaderBorder()"));

	if (!IsValid(this->HeaderBorder))
	{
		UE_LOG(LogTemp, Warning, TEXT("HeaderBorder null."));
		return;
	}

	USizeBoxSlot* ParentSlot = Cast<USizeBoxSlot>(this->HeaderBorder->Slot);
	ParentSlot->SetPadding(FMargin());
	ParentSlot->SetHorizontalAlignment(HAlign_Fill);
	ParentSlot->SetVerticalAlignment(VAlign_Fill);
	this->HeaderBorder->Slot = ParentSlot;
	
	FSlateBrush BorderBrush;
	BorderBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	FSlateBrushOutlineSettings OutlineSettings;
	OutlineSettings.CornerRadii = FVector4(10.f, 10.f, 0.f, 0.f);
	OutlineSettings.Width = 2.f;
	OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	BorderBrush.OutlineSettings = OutlineSettings;
	this->HeaderBorder->SetBrush(BorderBrush);
	this->HeaderBorder->SetBrushColor(FColor::Turquoise);

	this->SetIsEnabled(true);
	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UDetailsPopupHeaderWidget::InitializeParent()
{
	UE_LOG(LogTemp, Warning, TEXT("Entered InitializeParent()"));

	if (!IsValid(this->Parent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent null."));
		return;
	}

	this->Parent->MinDesiredWidth = this->ParentBoxMinWidth;
	this->Parent->MinDesiredHeight = this->ParentBoxMinHeight;
	this->Parent->MaxDesiredHeight = this->ParentBoxMaxHeight;

	this->Parent->SetIsEnabled(true);
	this->Parent->SetVisibility(ESlateVisibility::Visible);
	this->Parent->SetCursor(EMouseCursor::CardinalCross);
}