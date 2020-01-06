// Fill out your copyright notice in the Description page of Project Settings.


#include "WHUDWidget.h"
#include "Managers/WStatManager.h"
#include "Player/WCharacterStatComponent.h"
#include "Player/WPlayerState.h"
#include "Widgets/WMainWidget.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>


void UWHUDWidget::InitWidget(UWMainWidget* pMainWidget)
{
	if (nullptr != pMainWidget)
	{
		mpMainWidget = pMainWidget;
	}
}

void UWHUDWidget::BindCharacterStat(UWStatManager* pStatManager)
{
	if (nullptr != pStatManager)
	{
		mpStatManager = pStatManager;

		mpStatManager->OnHPChanged.AddUObject(this, &UWHUDWidget::UpdatePlayerHP);
		mpStatManager->OnMPChanged.AddUObject(this, &UWHUDWidget::UpdatePlayerMP);
	}	
}

void UWHUDWidget::UpdatePlayerHP()
{
	mpHPProgressBar->SetPercent(mpStatManager->GetHPRatio());
}

void UWHUDWidget::UpdatePlayerMP()
{
	mpMPProgressBar->SetPercent(mpStatManager->GetMPRatio());
}

void UWHUDWidget::BindPlayerState(AWPlayerState* pPlayerState)
{
	if (nullptr != pPlayerState)
	{
		mpPlayerState = pPlayerState;

		mpPlayerState->OnPlayerStateChanged.AddUObject(this, &UWHUDWidget::UpdatePlayerState);
	}
}

void UWHUDWidget::UpdatePlayerState()
{
	mpNameText->SetText(FText::FromString(mpPlayerState->GetPlayerName()));
	mpLevelText->SetText(FText::FromString((FString::FromInt(mpPlayerState->GetCharacterLevel()))));
}
