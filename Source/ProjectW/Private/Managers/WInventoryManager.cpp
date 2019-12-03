// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryManager.h"
#include "WItemBase.h"
#include "WPickupActor.h"
#include "USerWidget.h"


UWInventoryManager::UWInventoryManager()
{
	
}

void UWInventoryManager::InitWidget(UUserWidget* pWidget)
{
}

void UWInventoryManager::UpdateWidget()
{
}

int32 UWInventoryManager::AddItem(const TSubclassOf<class AWItemBase>& itemClass, int32 amount)
{
	items.Add(itemClass->GetName());

	return items.Num();
}

void UWInventoryManager::PrintInventory()
{
	FString sInventory = TEXT("");

	for (auto item : items)
	{
		sInventory.Append(item);
		sInventory.Append(TEXT(" . "));
	}

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, sInventory);
}

void UWInventoryManager::BeginPlay()
{
}
