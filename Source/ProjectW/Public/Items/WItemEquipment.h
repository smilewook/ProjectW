// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/WItemBase.h"
#include "WItemEquipment.generated.h"

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
	FORCEINLINE const FName& GetSocketName() const { return mSocketName; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* mpStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
	FName mSocketName;

	/* Properties */
public:

protected:

private:
};
