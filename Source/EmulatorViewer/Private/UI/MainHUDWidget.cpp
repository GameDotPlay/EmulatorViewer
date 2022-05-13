
#include "UI/MainHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UMainHUDWidget::SetInteractionModeText(FText InteractionModeText)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *InteractionModeText.ToString());
	this->InteractionModeLabel->SetText(InteractionModeText);
}

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Here is where I typically bind delegates,
	// and set up default appearance
}