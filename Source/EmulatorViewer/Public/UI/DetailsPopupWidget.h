

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DetailsPopupContentWidget.h"
#include "DetailsPopupHeaderWidget.h"
#include "DetailsPopupWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMULATORVIEWER_API UDetailsPopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UDetailsPopupContentWidget* GetContentWidget() { return this->ContentWidget; }

	void SetHeaderText(const FText& HeaderText) { this->HeaderWidget->SetHeaderText(HeaderText); }

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta=(BindWidget))
	UDetailsPopupHeaderWidget* HeaderWidget;

	UPROPERTY(meta = (BindWidget))
	UDetailsPopupContentWidget* ContentWidget;
};
