// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Managers/WContentManagerBase.h"
#include "WEquipmentManager.generated.h"


class AWItemEquipment;

struct FEquipmentSlotInfo;


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTW_API UWEquipmentManager : public UWContentManagerBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	UWEquipmentManager();

	virtual void InitManager(UWContentWidgetBase* pWidget) override;
	virtual void UpdateManager() override;
	virtual void Close() override;

	bool EquipSlot(AWItemEquipment* pItemEquipment);
	bool UnequipSlot(AWItemEquipment* pItemEquipment);

	/* Get/Set */
	FORCEINLINE const FEquipmentSlotInfo& GetWeaponSlot()	const { return mWeaponSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetShieldSlot()	const { return mShieldSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetHeadSlot()		const { return mHeadSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetShoulderSlot() const { return mShoulderSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetTopSlot()		const { return mTopSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetBottomSlot()	const { return mBottomSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetGloveSlot()	const { return mGloveSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetNecklaceSlot() const { return mNecklaceSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetEarringSlot()	const { return mEarringSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetRingSlot()		const { return mRingSlot; }
	FORCEINLINE const FEquipmentSlotInfo& GetBraceletSlot() const { return mBraceletSlot; }

	bool SetItemEquip(AWItemEquipment* pItemEquipment);

protected:

private:
	void InitSlot();

	// Equip
	bool EquipWeaponSlot(AWItemEquipment* pItemEquipment);
	bool EquipShieldSlot(AWItemEquipment* pItemEquipment);
	bool EquipHeadSlot(AWItemEquipment* pItemEquipment);
	bool EquipShoulderSlot(AWItemEquipment* pItemEquipment);
	bool EquipTopSlot(AWItemEquipment* pItemEquipment);
	bool EquipBottomSlot(AWItemEquipment* pItemEquipment);
	bool EquipGloveSlot(AWItemEquipment* pItemEquipment);
	bool EquipNecklaceSlot(AWItemEquipment* pItemEquipment);
	bool EquipEarringSlot(AWItemEquipment* pItemEquipment);
	bool EquipRingSlot(AWItemEquipment* pItemEquipment);
	bool EquipBraceletSlot(AWItemEquipment* pItemEquipment);

	// Unequip
	bool UnequipWeaponSlot();
	bool UnequipShieldSlot();
	bool UnequipHeadSlot();
	bool UnequipShoulderSlot();
	bool UnequipTopSlot();
	bool UnequipBottomSlot();
	bool UnequipGloveSlot();
	bool UnequipNecklaceSlot();
	bool UnequipEarringSlot();
	bool UnequipRingSlot();
	bool UnequipBraceletSlot();

	void UpdatePlayerStats(AWItemEquipment* pItemEquipment, bool isAdd);

	/* Properties */
public:

protected:
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mWeaponSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mShieldSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mHeadSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mShoulderSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mTopSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mBottomSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mGloveSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mNecklaceSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mEarringSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mRingSlot;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	FEquipmentSlotInfo mBraceletSlot;

private:

};
