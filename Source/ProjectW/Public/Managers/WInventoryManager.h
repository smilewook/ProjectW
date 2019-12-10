// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "WContentManagerBase.h"
#include "WInventoryManager.generated.h"


class UUserWidget;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWInventoryManager : public UWContentManagerBase
{
	GENERATED_BODY()

	/* Methods */
public:
	UWInventoryManager();

	virtual void InitWidget(UWContentWidgetBase* pWidget) override;
	virtual void UpdateWidget() override;

	void AddItem(int32 slotIndex);
	void RemoveItem(int32 slotIndex);
	void MoveItem(int32 targetSlotIndex, int32 fromSlotIndex);
	void SwapItem(int32 targetSlotIndex, int32 fromSlotIndex);
	void CombineItem(int32 targetSlotIndex, int32 fromSlotIndex);

	UFUNCTION(BlueprintCallable)
	void PrintInventory();

protected:
	virtual void BeginPlay() override;

private:

	/* Properties */
public:

protected:

private:
	

};
