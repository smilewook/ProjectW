// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
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

	virtual bool OnUse(FInventorySlotInfo* const pSlotInfo);

	/* Get/Set */

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* mpStaticMesh;

	/* Properties */
public:

protected:

private:
};
