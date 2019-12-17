// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "GameFramework/Actor.h"
#include "WItemBase.generated.h"


struct FInventorySlotInfo;
struct FItemInfo;

class AWPlayerCharacter;


UCLASS()
class PROJECTW_API AWItemBase : public AActor
{
	GENERATED_BODY()
	
	/* Methods */
public:
	AWItemBase();

	virtual void InitOwner(AActor* _pOwner);

	virtual bool OnUse(FInventorySlotInfo* const pSlotInfo) { return false; }

	/* Get/Set */
	FORCEINLINE const int32& GetItemID() const { return mItemInfo.ID; }
	FORCEINLINE const FItemInfo& GetItemInfo() const { return mItemInfo; }

protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	
protected:
	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	FItemInfo mItemInfo;

	AWPlayerCharacter* mpPlayer;

};
