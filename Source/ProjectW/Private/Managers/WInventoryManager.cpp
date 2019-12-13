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

	// �κ��丮 ���� �ʱ�ȭ.
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
	// ������ �߰�.
}

void UWInventoryManager::RemoveItem(const int32& slotIndex)
{
	// ������ ����.
}

void UWInventoryManager::MoveItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// ������ �̵�.
}

void UWInventoryManager::SwapItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// ������ ��ġ ��ü.
}

void UWInventoryManager::CombineItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// ������ ��ġ��. ���ýױ�.
}

void UWInventoryManager::PrintInventory()
{
	FString sInventory = TEXT("");

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, sInventory);
}


