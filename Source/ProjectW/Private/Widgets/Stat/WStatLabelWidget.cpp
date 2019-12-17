// Fill out your copyright notice in the Description page of Project Settings.


#include "WStatLabelWidget.h"

#include <Components/TextBlock.h>


void UWStatLabelWidget::NativeConstruct()
{
	//mpNameText->SetText(FText::FromString(TEXT("Attribute")));
	//mpValueText->SetText(FText::AsNumber(0));
}

void UWStatLabelWidget::InitWidget(EStatAttributeType statType, UWStatManager* pStatManager)
{
	mStatType = statType;
	FString statName = CONVERT_DISPLAYNAME_TO_STRING(L"EStatAttributeType", mStatType);
	mpNameText->SetText(FText::FromString(statName));
	
	if (nullptr != pStatManager)
	{
		mpStatManager = pStatManager;
	}
}

void UWStatLabelWidget::UpdateWidget(FStatInfo statInfo)
{
	mStatInfo = statInfo;

	mpValueText->SetText(FText::AsNumber((int32)mStatInfo.CurrentValue));
}