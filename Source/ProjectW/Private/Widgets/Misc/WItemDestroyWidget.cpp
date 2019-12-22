// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemDestroyWidget.h"
#include "ProjectWStructure.h"
#include "Items/WItemBase.h"
#include "Managers/WContentManagerBase.h"
#include "Managers/WInventoryManager.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/Inventory/WInventoryWidget.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UWItemDestroyWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);
}

void UWItemDestroyWidget::Show(FInventorySlotInfo* pSlotInfo)
{
	UWInventoryWidget* pInventoryWidget = Cast<UWInventoryWidget>(mpMainWidget->GetInventoryWidget());
	if (nullptr != pInventoryWidget)
	{
		FVector2D position = pInventoryWidget->GetWidgetCenterLocation();
		WLOG(Warning, TEXT("X : %f, Y : %f"), position.X, position.Y);
		//FGeometry geometry = mpMainWidget->GetCachedGeometry();
		//FVector2D position = geometry.AbsoluteToLocal(this->GetCachedGeometry().GetAbsolutePosition()) + this->GetCachedGeometry().GetLocalSize() / 2.0f;
		//this->SetPositionInViewport(position);

		pInventoryWidget->SetModal(true);
	}
	
	if (nullptr != pSlotInfo)
	{
		mpSlotInfo = pSlotInfo;
		if (nullptr != mpSlotInfo->pItemClass)
		{
			FItemInfo itemInfo = mpSlotInfo->pItemClass->GetItemInfo();
			mpNameText->SetText(FText::FromName(itemInfo.Name));
		}
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UWItemDestroyWidget::Hide()
{
	mpSlotInfo = nullptr;
	SetVisibility(ESlateVisibility::Hidden);

	UWInventoryWidget* pInventoryWidget = Cast<UWInventoryWidget>(mpMainWidget->GetInventoryWidget());
	if (nullptr != pInventoryWidget)
	{
		pInventoryWidget->SetModal(false);
	}
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

