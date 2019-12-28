// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "Items/WItemBase.h"
#include "WItemPotion.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API AWItemPotion : public AWItemBase
{
	GENERATED_BODY()
	
		/* Methods */
public:
	AWItemPotion();

	virtual void InitOwner(AActor* pOwner) override;
	virtual bool OnUse(FInventorySlotInfo* const pSlotInfo) override;

	/* Properties */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* mpStaticMesh;

};
