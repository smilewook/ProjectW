// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryManager.h"
#include "Actors/WPickupActor.h"
#include "Items/WItemBase.h"
#include "Widgets/Inventory/WInventoryWidget.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"

#include <UserWidget.h>


UWInventoryManager::UWInventoryManager()
{
	
}

void UWInventoryManager::UpdateWidget()
{
}

bool UWInventoryManager::AddItem(const TSubclassOf<AWItemBase>& newItemClass, int32 amount)
{
	int slotIndex = SearchEmptySlotIndex();
	if (slotIndex != -1)
	{
		mSlots[slotIndex].ItemClass = newItemClass;
		mSlots[slotIndex].Amount = amount;
		mSlots[slotIndex].pSlotWidget->UpdateWidget();
		return true;
	}

	return false;
}

bool UWInventoryManager::RemoveItem(const int32& slotIndex)
{
	// 아이템 제거.
	return false;
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

void UWInventoryManager::InitWidget(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitWidget(pWidget);

	// 인벤토리 슬롯 초기화.
	CreateSlot();
}
void UWInventoryManager::BeginPlay()
{
	Super::BeginPlay();
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

int32 UWInventoryManager::SearchEmptySlotIndex()
{
	for (int32 i = 0; i < mSlots.Num(); i++)
	{
		if (nullptr == mSlots[i].ItemClass)
		{
			return i;
		}
	}

	return -1;
}

void UWInventoryManager::PrintInventory()
{
	FString sInventory = TEXT("");

	for (FInventorySlotInfo elem : mSlots)
	{
		
	}

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, sInventory);
}


