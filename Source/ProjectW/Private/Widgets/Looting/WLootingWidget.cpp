// Fill out your copyright notice in the Description page of Project Settings.


#include "WLootingWidget.h"
#include "Items/WItemBase.h"
#include "Managers/WContentManagerBase.h"
#include "Managers/WLootingManager.h"
#include "Widgets/Looting/WLootingSlotWidget.h"
#include "Widgets/WMainWidget.h"

#include <Components/Button.h>
#include <Components/UniformGridSlot.h>
#include <Components/VerticalBox.h>


bool UWLootingWidget::CreateSlots()
{
	mpLootingSlots->ClearChildren();

	if (nullptr != mSlotWidgetClass)
	{
		UWLootingManager* pLootingManager = Cast<UWLootingManager>(mpContentManager);
		//WLOG(Warning, TEXT("UWLootingWidget::CreateSlots() slotCount = %d"), pLootingManager->GetSlotCount());
		for (int32 i = 0; i < pLootingManager->GetSlotCount(); i++)		
		{
			AWItemBase* pItemClass = pLootingManager->GetItemInfo(i)->ItemClass.GetDefaultObject();
			if (nullptr != pItemClass && (pLootingManager->GetItemInfo(i)->Amount > 0))
			{
				UWLootingSlotWidget* pLootingSlotWidget = CreateWidget<UWLootingSlotWidget>(GetWorld(), mSlotWidgetClass);
				pLootingSlotWidget->InitWidget(pLootingManager, i);
				pLootingSlotWidget->UpdateWidget();
				pLootingSlotWidget->SetTooltipWidget(mpMainWidget->GetTooltipWidget());

				mpLootingSlots->AddChildToVerticalBox(pLootingSlotWidget);
			}
		}

		return true;
	}
	else
	{
		WLOG(Warning, TEXT("UWLootingWidget::CreateSlots() Failed!"));
		return false;
	}
}

void UWLootingWidget::RemoveSlots()
{
	mpLootingSlots->ClearChildren();
}

void UWLootingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mpCloseButton->OnClicked.AddDynamic(this, &UWLootingWidget::OnCloseButtonClicked);
}

void UWLootingWidget::OnCloseButtonClicked()
{
	mpContentManager->Close();
}

FReply UWLootingWidget::NativeOnMouseButtonDown(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWContentWidgetBase::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
	}

	return FReply::Unhandled();
}

void UWLootingWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	UWContentWidgetBase::NativeOnDragDetected(inGeometry, inMouseEvent, outOperation);
}


