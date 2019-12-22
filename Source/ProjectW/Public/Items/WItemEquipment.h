// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Items//WItemBase.h"
#include "WItemEquipment.generated.h"


struct FInventorySlotInfo;


/**
 * 
 */
UCLASS()
class PROJECTW_API AWItemEquipment : public AWItemBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	AWItemEquipment();

	virtual bool OnUse(FInventorySlotInfo* const pSlotInfo);

	/* Get/Set */
	FORCEINLINE const EItemEquipType& GetItemEquipType() const { return mItemEquipType; }
	FORCEINLINE const FName& GetSocketName() const { return mSocketName; }

	/* Properties */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	UStaticMeshComponent* mpStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Configuration | Equip")
	FName mSocketName;

	UPROPERTY(EditAnywhere, Category = "Configuration | Equip")
	EItemEquipType mItemEquipType;

};
