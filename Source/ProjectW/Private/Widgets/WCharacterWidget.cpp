// Fill out your copyright notice in the Description page of Project Settings.


#include "WCharacterWidget.h"
#include "Player/WCharacterStatComponent.h"

#include <Components/ProgressBar.h>


void UWCharacterWidget::BindCharacterStat(class UWCharacterStatComponent* pNewCharacterStat)
{
	WCHECK(nullptr != pNewCharacterStat);
	
	mCurrentCharacterStat = pNewCharacterStat;
	pNewCharacterStat->OnHPChanged.AddUObject(this, &UWCharacterWidget::UpdateHPWidget);
}

void UWCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mpHPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	WCHECK(nullptr != mpHPProgressBar);
	UpdateHPWidget();
}

void UWCharacterWidget::UpdateHPWidget()
{
	if (mCurrentCharacterStat.IsValid())
	{
		if (nullptr != mpHPProgressBar)
		{
			mpHPProgressBar->SetPercent(mCurrentCharacterStat->GetHPRatio());
		}
	}
}

