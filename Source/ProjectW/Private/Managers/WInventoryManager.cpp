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

	// ���� �ʱ�ȭ.
}

void UWInventoryManager::UpdateWidget()
{
}

void UWInventoryManager::AddItem(int32 slotIndex)
{
	// ������ �߰�.
}

void UWInventoryManager::RemoveItem(int32 slotIndex)
{
	// ������ ����.
}

void UWInventoryManager::MoveItem(int32 targetSlotIndex, int32 fromSlotIndex)
{
	// ������ �̵�.
}

void UWInventoryManager::SwapItem(int32 targetSlotIndex, int32 fromSlotIndex)
{
	// ������ ��ġ ��ü.
}

void UWInventoryManager::CombineItem(int32 targetSlotIndex, int32 fromSlotIndex)
{
	// ������ ��ġ��. ���ýױ�.
}

void UWInventoryManager::PrintInventory()
{
	FString sInventory = TEXT("");

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, sInventory);
}


