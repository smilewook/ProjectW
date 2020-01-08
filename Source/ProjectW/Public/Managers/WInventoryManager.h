// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWStructure.h"
#include "WContentManagerBase.h"
#include "WInventoryManager.generated.h"


class AWItemBase;
class UWContentWidgetBase;


/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTW_API UWInventoryManager : public UWContentManagerBase
{
	GENERATED_BODY()

	/* Methods */
public:
	UWInventoryManager();

	virtual void InitManager(UWContentWidgetBase* pWidget) override;
	virtual void UpdateManager() override;
	virtual void Close() override;

	bool AddItem(AWItemBase* newItemClass, int32 amount = 1);
	bool AddItemByIndex(const int32& slotIndex, AWItemBase* newItemClass, int32 amount);
	bool RemoveItem(const int32& slotIndex);
	void MoveItem(const int32& targetSlotIndex, const int32& fromSlotIndex);
	void SwapItem(const int32& targetSlotIndex, const int32& fromSlotIndex);
	void CombineItem(const int32& targetSlotIndex, const int32& fromSlotIndex);
	void ThrowAwayItem(const int32& slotIndex);
	void ShowAcquireItem(AWItemBase* newItemClass, int32 amount = 1);

	/* Get/Set */
	FORCEINLINE const TArray<FInventorySlotInfo>& GetSlots() const { return mSlots; }
	FORCEINLINE const FInventorySlotInfo& GetSlot(int32 slotIndex) const { return mSlots[slotIndex]; }

protected:
	virtual void BeginPlay() override;

private:
	void CreateSlot();
	int32 SearchEmptySlotIndex();
	bool IsEmptySlot(int32 slotIndex);

	/* Properties */
public:

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	int mSlotMaxNum = 36;

	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	int mSlotRowNum = 6;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<FInventorySlotInfo> mSlots;

private:
	

};
