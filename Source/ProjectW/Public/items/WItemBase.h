// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"

#include "GameFramework/Actor.h"
#include "WItemBase.generated.h"

UCLASS()
class PROJECTW_API AWItemBase : public AActor
{
	GENERATED_BODY()
	
	/* Methods */
public:
	AWItemBase();

	virtual void InitItemOwner(AActor* _pOwner);
	virtual bool OnUse(FInventorySlotInfo* const pSlotInfo) { return false; }

	/* Get/Set */
	FORCEINLINE const FItemInfo& GetItemInfo() const { return mpItemInfo; }
	FORCEINLINE const int32& GetItemID() const { return mpItemInfo.ID; }
	FORCEINLINE const FName& GetItemName() const { return mpItemInfo.Name; }


protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	
protected:
	UPROPERTY(EditAnywhere, Category = "Configuration")
	struct FItemInfo mpItemInfo;

	class AWPlayerCharacter* mpPlayer;

};
