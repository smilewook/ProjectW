// Fill out your copyright notice in the Description page of Project Settings.


#include "WStatWidget.h"
#include "Managers/WStatManager.h"
#include "Widgets/Stat/WStatLabelWidget.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>


void UWStatWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);

	mpStatManager = Cast<UWStatManager>(pContentManager);
}

void UWStatWidget::CreateStatAttribute()
{
	mpDefaultStats->ClearChildren();
	mpSpecialStats->ClearChildren();
	
	if (nullptr != mpStatManager && nullptr != mStatLabelWidgetClass)
	{
		for (auto stat : mpStatManager->GetStats())
		{
			UWStatLabelWidget* pStatLabelWidget = CreateWidget<UWStatLabelWidget>(GetWorld(), mStatLabelWidgetClass);
			
			pStatLabelWidget->InitWidget(stat.Key, mpStatManager);
			pStatLabelWidget->UpdateWidget(stat.Value);
			mpStatManager->AddStatAttribute(pStatLabelWidget);

			if (EStatAttributeType::StatAttribute_None == stat.Key || EStatAttributeType::StatAttribute_Special == stat.Key)
			{
				continue;
			}

			if (stat.Key < EStatAttributeType::StatAttribute_Special)
			{
				mpDefaultStats->AddChildToVerticalBox(pStatLabelWidget);
			}
			else
			{
				mpSpecialStats->AddChildToVerticalBox(pStatLabelWidget);
			}
		}
	}
}

void UWStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mpCloseButton->OnClicked.AddDynamic(this, &UWStatWidget::OnCloseButtonClicked);
}

void UWStatWidget::OnCloseButtonClicked()
{
	mpContentManager->Close();
}

FReply UWStatWidget::NativeOnMouseButtonDown(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWContentWidgetBase::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
	}

	return FReply::Unhandled();
}

void UWStatWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	UWContentWidgetBase::NativeOnDragDetected(inGeometry, inMouseEvent, outOperation);
}
