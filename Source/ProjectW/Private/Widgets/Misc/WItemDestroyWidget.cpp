// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemDestroyWidget.h"
#include "ProjectWStructure.h"
#include "WMainWidget.h"
#include "WContentManagerBase.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UWItemDestroyWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);
}

void UWItemDestroyWidget::Show(FInventorySlotInfo* pSlotInfo)
{
	if (nullptr != pSlotInfo)
	{
		mpSlotInfo = pSlotInfo;
		if (nullptr != mpSlotInfo->ItemClass)
		{
			FItemInfo itemInfo = mpSlotInfo->ItemClass.GetDefaultObject()->GetItemInfo();
			mpNameText->SetText(FText::FromName(itemInfo.Name));
		}
	}
}

void UWItemDestroyWidget::Hide()
{
	mpSlotInfo = nullptr;
	SetVisibility(ESlateVisibility::Hidden);
}

void UWItemDestroyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mpConfirmButton->OnClicked.AddDynamic(this, &UWItemDestroyWidget::OnConfrimButtonClicked);
	mpCancelButton->OnClicked.AddDynamic(this, &UWItemDestroyWidget::OnCancelButtonClicked);
}

void UWItemDestroyWidget::OnConfrimButtonClicked()
{
	UWInventoryManager* pInventory = Cast<UWInventoryManager>(mpContentManager);
	if (nullptr != pInventory)
	{
		pInventory->RemoveItem(mpSlotInfo->SlotIndex);

		Hide();
	}
	
}

void UWItemDestroyWidget::OnCancelButtonClicked()
{
	Hide();
}

FReply UWItemDestroyWidget::NativeOnMouseButtonDown(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWContentWidgetBase::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
	}

	return FReply::Unhandled();
}

void UWItemDestroyWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	UWContentWidgetBase::NativeOnDragDetected(inGeometry, inMouseEvent, outOperation);
}

