// Fill out your copyright notice in the Description page of Project Settings.


#include "WLootingManager.h"
#include "ProjectWStructure.h"
#include "Widgets/Looting/WLootingWidget.h"


UWLootingManager::UWLootingManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	mSlotCount = 0;
}

void UWLootingManager::InitManager(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitManager(pWidget);
}

void UWLootingManager::UpdateManager()
{
}

void UWLootingManager::Open()
{
	UWLootingWidget* pLootingWidget = Cast<UWLootingWidget>(mpWidget);
	pLootingWidget->SetContentManager(this);
	pLootingWidget->CreateSlots();

	CheckExistSlotCount();

	UWContentManagerBase::Open();
}

void UWLootingManager::Close()
{
	UWLootingWidget* pLootingWidget = Cast<UWLootingWidget>(mpWidget);
	pLootingWidget->RemoveSlots();

	UWContentManagerBase::Close();
}

bool UWLootingManager::AddItem(const TSubclassOf<AWItemBase>& newItemClass, int32 amount)
{
	mSlots.Emplace(FLootingSlotInfo(newItemClass, amount));
	
	return true;
}

bool UWLootingManager::RemoveItem(const int32& slotIndex)
{

	if (mSlots.IsValidIndex(slotIndex) && (mSlots[slotIndex].Amount > 0))
	{
		mSlots[slotIndex].ItemClass = nullptr;
		mSlots[slotIndex].Amount = 0;
		mSlotCount--;
		if (mSlotCount == 0)
		{
			GetOwner()->Destroy();
		}
		//WLOG(Warning, TEXT("UWLootingManager::RemoveItem() Successed!! slotIndex = %d, slotCount = %d,"), slotIndex, mSlotCount);
		return true;
	}

	return false;
}

void UWLootingManager::CheckExistSlotCount()
{
	mSlotCount = 0;
	for (int32 i = 0; i < GetSlotCount(); i++)
	{
		if (mSlots[i].Amount > 0) mSlotCount++;
	}
	//WLOG(Warning, TEXT("UWLootingManager::CheckExistSlotCount() slotCount = %d,"), mSlotCount);
}

const FLootingSlotInfo* UWLootingManager::GetItemInfo(int32 slotIndex)
{
	if (mSlots.IsValidIndex(slotIndex))
	{
		return &mSlots[slotIndex];
	}

	return nullptr;
}
