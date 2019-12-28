// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Items/WItemBase.h"
#include "WItemEquipment.generated.h"


struct FInventorySlotInfo;

class UArrowComponent;
class USkeletalMeshComponent;
class USkeletalMesh;
class UCapsuleComponent;


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

	virtual void InitOwner(AActor* pOwner) override;
	virtual bool OnUse(FInventorySlotInfo* const pSlotInfo) override;

	/* Get/Set */
	FORCEINLINE USkeletalMesh* const& GetWeaponMesh() const { return mpItemMesh; }
	FORCEINLINE const FName& GetSocketName() const { return mSocketName; }
	FORCEINLINE const EItemEquipType& GetItemEquipType() const { return mItemEquipType; }

	/* Properties */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UArrowComponent* mpArrow;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* mpCollision;

// 	UPROPERTY(VisibleAnywhere, Category = "Components")
// 	USkeletalMeshComponent* mpItemMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	USkeletalMesh* mpItemMesh;

// 	UPROPERTY(VisibleAnywhere, Category = "Components")
// 	UArrowComponent* mpArrow;
// 
// 	UPROPERTY(VisibleAnywhere, Category = "Components")
// 	UCapsuleComponent* mpCollision;
// 
// 	UPROPERTY(VisibleAnywhere, Category = "Components")
// 	UStaticMeshComponent* mpItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Configuration | Equip")
	FName mSocketName;

	UPROPERTY(EditAnywhere, Category = "Configuration | Equip")
	EItemEquipType mItemEquipType;

};
