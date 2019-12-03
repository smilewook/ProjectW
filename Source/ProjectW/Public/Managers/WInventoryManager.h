// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WContentManagerBase.h"
#include "WInventoryManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API UWInventoryManager : public UWContentManagerBase
{
	GENERATED_BODY()

	/* Methods */
public:
	UWInventoryManager();

	virtual void InitWidget(UUserWidget* pWidget) override;
	virtual void UpdateWidget() override;

	int32 AddItem(const TSubclassOf<class AWItemBase>& itemClass, int32 amount);

	UFUNCTION(BlueprintCallable)
	void PrintInventory();

protected:
	virtual void BeginPlay() override;

private:

	/* Properties */
public:

protected:

private:
	//TArray<TSubclassOf<class AWItemBase>> items;
	TArray<FString> items;

};
