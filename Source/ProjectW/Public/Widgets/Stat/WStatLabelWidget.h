// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Blueprint/UserWidget.h"
#include "WStatLabelWidget.generated.h"


class UWStatManager;

class UTextBlock;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWStatLabelWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	void InitWidget(EStatAttributeType statType, UWStatManager* pStatManager);
	void UpdateWidget(FStatInfo statInfo);

	/* Get/Set */
	FORCEINLINE const EStatAttributeType& GetStatType() const { return mStatType; }

protected:
	virtual void NativeConstruct() override;

	/* Properties */
protected:
	UPROPERTY()
	UTextBlock* mpNameText;

	UPROPERTY()
	UTextBlock* mpValueText;

private:
	EStatAttributeType mStatType;
	FStatInfo mStatInfo;

	UWStatManager* mpStatManager;

};
