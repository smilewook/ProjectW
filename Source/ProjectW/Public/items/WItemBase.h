// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Actor.h"
#include "WItemBase.generated.h"

UCLASS()
class PROJECTW_API AWItemBase : public AActor
{
	GENERATED_BODY()
	
	/* Methods */
public:
	AWItemBase();

	/* Get/Set */
	FORCEINLINE const FString& GetItemName() const { return mName; }
	FORCEINLINE const int& GetID() const { return mID; }

protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	
protected:
	int32 mID;

	FString mName;

};
