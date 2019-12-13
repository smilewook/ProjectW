// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryManager.h"
#include "Actors/WPickupActor.h"
#include "Items/WItemBase.h"
#include "Widgets/Inventory/WInventoryWidget.h"

#include <UserWidget.h>


UWInventoryManager::UWInventoryManager()
{
	
}

void UWInventoryManager::BeginPlay()
{
	Super::BeginPlay();
}

void UWInventoryManager::InitWidget(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitWidget(pWidget);

	// 인벤토리 슬롯 초기화.
	CreateSlot();
}

void UWInventoryManager::CreateSlot()
{
	mSlots.Empty();
	mSlots.SetNum(mSlotMaxNum);

	UWInventoryWidget* pWidget = Cast<UWInventoryWidget>(mpWidget);

	if (nullptr != pWidget)
	{
		for (int i = 0; i < mSlots.Num(); ++i)
		{
			int row = (i / mSlotRowNum);
			int column = (i % mSlotRowNum);

			mSlots[i].SlotIndex = i;

			pWidget->CreateSlot(&mSlots[i], row, column);
		}
	}
}

void UWInventoryManager::UpdateWidget()
{
}

void UWInventoryManager::AddItem(AWItemBase* pItem)
{
	// 아이템 추가.
}

void UWInventoryManager::RemoveItem(const int32& slotIndex)
{
	// 아이템 제거.
}

void UWInventoryManager::MoveItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// 아이템 이동.
}

void UWInventoryManager::SwapItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// 아이템 위치 교체.
}

void UWInventoryManager::CombineItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// 아이템 합치기. 스택쌓기.
}

void UWInventoryManager::PrintInventory()
{
	FString sInventory = TEXT("");

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, sInventory);
}


