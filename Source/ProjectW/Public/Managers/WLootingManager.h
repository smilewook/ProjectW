// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Managers/WContentManagerBase.h"
#include "WLootingManager.generated.h"


class AWItemBase;

struct FLootingSlotInfo;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWLootingManager : public UWContentManagerBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	UWLootingManager();

	virtual void InitManager(UWContentWidgetBase* pWidget) override;
	virtual void UpdateManager() override;

	virtual void Open() override;
	virtual void Close() override;

	bool AddItem(const TSubclassOf<AWItemBase>& newItemClass, int32 amount = 1);
	bool RemoveItem(const int32& slotIndex);
	void CheckExistSlotCount();

	/* Get/Set */
	FORCEINLINE const int32 GetSlotCount() const { return mSlots.Num(); }
	const FLootingSlotInfo* GetItemInfo(int32 slotIndex);

	/* Properties */
protected:
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TArray<FLootingSlotInfo> mSlots;

private:
	int32 mSlotCount;
};
