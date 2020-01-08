// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryManager.h"
#include "Actors/WPickupActor.h"
#include "Items/WItemBase.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/WContentWidgetBase.h"
#include "Widgets/Inventory/WInventoryWidget.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"
#include "Widgets/Misc/WItemDestroyWidget.h"

#include <UserWidget.h>


UWInventoryManager::UWInventoryManager()
{
	
}

void UWInventoryManager::InitManager(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitManager(pWidget);

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

void UWInventoryManager::UpdateManager()
{
	// something like that
}

void UWInventoryManager::Close()
{
	UWContentManagerBase::Close();

	// �κ��丮�� ���õ� ������&���� ���ͷ���.
	UWItemDestroyWidget* itemDestroyWidget = mpWidget->GetMainWidget()->GetItemDestroyWidget();
	itemDestroyWidget->Hide();
}

bool UWInventoryManager::AddItem(AWItemBase* newItemClass, int32 amount)
{
	if (nullptr != newItemClass)
	{
		newItemClass->InitOwner(GetOwner());

		// ������ �߰�.
		int slotIndex = SearchEmptySlotIndex();
		if (slotIndex != -1)
		{
			mSlots[slotIndex].pItemClass = newItemClass;
			mSlots[slotIndex].Amount = amount;
			mSlots[slotIndex].pSlotWidget->UpdateWidget();

			ShowAcquireItem(newItemClass, amount);

			return true;
		}
	}	

	return false;
}

bool UWInventoryManager::AddItemByIndex(const int32 & slotIndex, AWItemBase* newItemClass, int32 amount)
{
	if (true == IsEmptySlot(slotIndex))
	{
		mSlots[slotIndex].pItemClass = newItemClass;
		mSlots[slotIndex].Amount = amount;
		mSlots[slotIndex].pSlotWidget->UpdateWidget();

		return true;
	}

	WLOG(Warning, TEXT("mSlot[%d] has data!!"));
	return false;
}

bool UWInventoryManager::RemoveItem(const int32& slotIndex)
{
	// ������ ����.
	if (nullptr != mSlots[slotIndex].pItemClass)
	{
		mSlots[slotIndex].Amount = 0;
		mSlots[slotIndex].pItemClass->Destroy();
		mSlots[slotIndex].pItemClass = nullptr;
		mSlots[slotIndex].pSlotWidget->UpdateWidget();

		return true;
	}
	else
	{
		WLOG(Warning, TEXT("mSlots[&d] is Empty!"), slotIndex);
		return false;
	}
}

void UWInventoryManager::MoveItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// ������ �̵�.
	mSlots[targetSlotIndex].Amount = mSlots[fromSlotIndex].Amount;
	mSlots[targetSlotIndex].pItemClass = mSlots[fromSlotIndex].pItemClass;

	mSlots[fromSlotIndex].Amount = 0;
	mSlots[fromSlotIndex].pItemClass->Destroy();
	mSlots[fromSlotIndex].pItemClass = nullptr;

	mSlots[targetSlotIndex].pSlotWidget->UpdateWidget();
	mSlots[fromSlotIndex].pSlotWidget->UpdateWidget();
}

void UWInventoryManager::SwapItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// ������ ��ġ ��ü.
	int32 tempAmount = mSlots[targetSlotIndex].Amount;
	AWItemBase* tempItemClass = mSlots[targetSlotIndex].pItemClass;

	mSlots[targetSlotIndex].Amount = mSlots[fromSlotIndex].Amount;
	mSlots[targetSlotIndex].pItemClass = mSlots[fromSlotIndex].pItemClass;

	mSlots[fromSlotIndex].Amount = tempAmount;
	mSlots[fromSlotIndex].pItemClass = tempItemClass;

	mSlots[targetSlotIndex].pSlotWidget->UpdateWidget();
	mSlots[fromSlotIndex].pSlotWidget->UpdateWidget();
}

void UWInventoryManager::CombineItem(const int32& targetSlotIndex, const int32& fromSlotIndex)
{
	// ������ ��ġ��. ���ýױ�.
	// ����. ���ü��� ������ ���� ��쵵 ����ϱ�.
	mSlots[targetSlotIndex].Amount += mSlots[fromSlotIndex].Amount;

	mSlots[fromSlotIndex].Amount = 0;
	mSlots[fromSlotIndex].pItemClass->Destroy();
	mSlots[fromSlotIndex].pItemClass = nullptr;

	mSlots[targetSlotIndex].pSlotWidget->UpdateWidget();
	mSlots[fromSlotIndex].pSlotWidget->UpdateWidget();
}

void UWInventoryManager::ThrowAwayItem(const int32 & slotIndex)
{
	// ������ �ı� ������ �ѱ�.
	UWItemDestroyWidget* itemDestroyWidget = mpWidget->GetMainWidget()->GetItemDestroyWidget();
	FInventorySlotInfo* slotInfo = &(mSlots[slotIndex]);
	itemDestroyWidget->Show(slotInfo);
}

void UWInventoryManager::ShowAcquireItem(AWItemBase* newItemClass, int32 amount)
{
	if (nullptr != mpWidget->GetMainWidget())
	{
		mpWidget->GetMainWidget()->AddAcquireItemQueue(newItemClass, amount);
	}
}

void UWInventoryManager::BeginPlay()
{
	Super::BeginPlay();
}

int32 UWInventoryManager::SearchEmptySlotIndex()
{
	for (int32 i = 0; i < mSlots.Num(); i++)
	{
		if (nullptr == mSlots[i].pItemClass)
		{
			return i;
		}
	}

	return -1;
}

bool UWInventoryManager::IsEmptySlot(int32 slotIndex)
{
	return false == ::IsValid(mSlots[slotIndex].pItemClass);
}

