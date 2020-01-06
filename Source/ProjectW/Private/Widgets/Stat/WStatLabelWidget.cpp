// Fill out your copyright notice in the Description page of Project Settings.


#include "WStatLabelWidget.h"

#include <Components/TextBlock.h>

#define LOCTEXT_NAMESPACE "Format"


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

	int32 currentValue = mStatInfo.CurrentValue;
	int32 maxValue = mStatInfo.MaxValue;
	FText format;

	switch (mStatType)
	{
	case EStatAttributeType::StatAttribute_Level:
	case EStatAttributeType::StatAttribute_Attack:
	case EStatAttributeType::StatAttribute_Defense:
	case EStatAttributeType::StatAttribute_Critical:
	case EStatAttributeType::StatAttribute_Dodge:
		format = FText::AsNumber(maxValue);
		break;
	case EStatAttributeType::StatAttribute_Exp:
	{
		int32 result = currentValue <= 0 ? 0 : (float)currentValue / (float)maxValue * 100;
		format = FText::Format(LOCTEXT("Format", "{0}%"), result);
		break;
	}		
	case EStatAttributeType::StatAttribute_HP:
	case EStatAttributeType::StatAttribute_MP:
		format = FText::Format(LOCTEXT("Format", "{0}/{1}"), currentValue, maxValue);
		break;
	case EStatAttributeType::StatAttribute_None:
	case EStatAttributeType::StatAttribute_Special:
	case EStatAttributeType::StatAttribute_Max:
	default:
		break;
	}

	mpValueText->SetText(format);
}