// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryManager.h"
#include "Actors/WPickupActor.h"
#include "Items/WItemBase.h"

#include <UserWidget.h>


UWInventoryManager::UWInventoryManager()
{
	
}

void UWInventoryManager::BeginPlay()
{

}

void UWInventoryManager::InitWidget(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitWidget(pWidget);

	// 슬롯 초기화.
}

void UWInventoryManager::UpdateWidget()
{
}

void UWInventoryManager::AddItem(int32 slotIndex)
{
	// 아이템 추가.
}

void UWInventoryManager::RemoveItem(int32 slotIndex)
{
	// 아이템 제거.
}

void UWInventoryManager::MoveItem(int32 targetSlotIndex, int32 fromSlotIndex)
{
	// 아이템 이동.
}

void UWInventoryManager::SwapItem(int32 targetSlotIndex, int32 fromSlotIndex)
{
	// 아이템 위치 교체.
}

void UWInventoryManager::CombineItem(int32 targetSlotIndex, int32 fromSlotIndex)
{
	// 아이템 합치기. 스택쌓기.
}

void UWInventoryManager::PrintInventory()
{
	FString sInventory = TEXT("");

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, sInventory);
}


