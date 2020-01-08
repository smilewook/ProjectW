// Fill out your copyright notice in the Description page of Project Settings.


#include "WMainWidget.h"
#include "WSlotDragDropOperation.h"
#include "Items/WItemBase.h"
#include "Managers/WEquipmentManager.h"
#include "Managers/WInventoryManager.h"
#include "Managers/WStatManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Equipment/WEquipmentWidget.h"
#include "Widgets/Inventory/WInventoryWidget.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"
#include "Widgets/Misc/WAcquireItemWidget.h"
#include "Widgets/Misc/WItemDestroyWidget.h"
#include "Widgets/Misc/WTooltipWidget.h"
#include "Widgets/Player/WHUDWidget.h"
#include "Widgets/Stat/WStatWidget.h"


void UWMainWidget::NativeConstruct()
{
	
}

bool UWMainWidget::NativeOnDrop(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation)
{
	WLOG(Warning, TEXT("UWMainWidget::NativeOnDrop() ?"));

	return false;
}

bool UWMainWidget::InitWidget(AWPlayerCharacter* pPlayer)
{
	if (nullptr != pPlayer)
	{
		mpPlayer = pPlayer;
	}

	if (nullptr != mTooltipWidgetClass)
	{
		mpToolipWidget = CreateWidget<UWTooltipWidget>(GetWorld(), mTooltipWidgetClass);
		mpToolipWidget->InitWidget(this, nullptr);
	}

	if (nullptr != mAcquireWidgetClass)
	{
		//mpAcquireItemWidget = CreateWidget<UWAcquireItemWidget>(GetWorld(), mAcquireWidgetClass);
	}
	
	// °¢ À§Á¬¿¡ ¸ÞÀÎ/ÄÁÅÙÃ÷ ¸Å´ÏÀú µî·Ï.
	mpHUDWidget->InitWidget(this);
	mpInventoryWidget->InitWidget(this, mpPlayer->GetInventoryManager());
	mpItemDestroyWidget->InitWidget(this, mpPlayer->GetInventoryManager());
	mpStatWidget->InitWidget(this, mpPlayer->GetStatManager());
	mpEquipmentWidget->InitWidget(this, mpPlayer->GetEquipmentManager());	

	return true;
}

void UWMainWidget::AddAcquireItemQueue(AWItemBase* newItemClass, int32 amount)
{
	if (mAcquireItemsQueue.Num() > 0)
	{
		FInventorySlotInfo inventorySlotInfo;
		inventorySlotInfo.pItemClass = newItemClass;
		inventorySlotInfo.Amount = amount;
		mAcquireItemsQueue.Emplace(inventorySlotInfo);
	}
	else
	{
		FInventorySlotInfo inventorySlotInfo;
		inventorySlotInfo.pItemClass = newItemClass;
		inventorySlotInfo.Amount = amount;
		mAcquireItemsQueue.Emplace(inventorySlotInfo);
		
		mpAcquireItemWidget->InitWidget(newItemClass, amount, mAcquireDuration, this);
		mpAcquireItemWidget->Show();
	}
}

void UWMainWidget::EndAcquireItemMessage()
{
	mAcquireItemsQueue.RemoveAt(0);

	if (mAcquireItemsQueue.Num() > 0)
	{
		mpAcquireItemWidget->InitWidget(mAcquireItemsQueue[0].pItemClass, mAcquireItemsQueue[0].Amount, mAcquireDuration, this);
		mpAcquireItemWidget->Show();
	}
}