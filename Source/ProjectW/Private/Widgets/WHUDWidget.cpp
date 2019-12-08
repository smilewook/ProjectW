// Fill out your copyright notice in the Description page of Project Settings.


#include "WHUDWidget.h"
#include "Player/WCharacterStatComponent.h"
#include "Player/WPlayerState.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>


void UWHUDWidget::BindCharacterStat(UWCharacterStatComponent* pCharacterStat)
{
	WCHECK(nullptr != pCharacterStat);
	mCurrentCharacterStat = pCharacterStat;
	pCharacterStat->OnHPChanged.AddUObject(this, &UWHUDWidget::UpdateCharacterStat);
}

void UWHUDWidget::BindPlayerState(AWPlayerState* pPlayerState)
{
	WCHECK(nullptr != pPlayerState);
	mCurrentPlayerState = pPlayerState;
	pPlayerState->OnPlayerStateChanged.AddUObject(this, &UWHUDWidget::UpdatePlayerState);
}

void UWHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	WCHECK(nullptr != mHPBar);

	mExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	WCHECK(nullptr != mExpBar);

	mPlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	WCHECK(nullptr != mPlayerName);

	mPlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	WCHECK(nullptr != mPlayerLevel);

	mCurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	WCHECK(nullptr != mCurrentScore);

	mHighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	WCHECK(nullptr != mHighScore);
}

void UWHUDWidget::UpdateCharacterStat()
{
	WCHECK(mCurrentCharacterStat.IsValid());

	mHPBar->SetPercent(mCurrentCharacterStat->GetHPRatio());
}

void UWHUDWidget::UpdatePlayerState()
{
	WCHECK(mCurrentPlayerState.IsValid());

	mExpBar->SetPercent(mCurrentPlayerState->GetExpRatio());
	mPlayerName->SetText(FText::FromString(mCurrentPlayerState->GetPlayerName()));
	mPlayerLevel->SetText(FText::FromString((FString::FromInt(mCurrentPlayerState->GetCharacterLevel()))));
	mCurrentScore->SetText(FText::FromString((FString::FromInt(mCurrentPlayerState->GetGameScore()))));
	mHighScore->SetText(FText::FromString(FString::FromInt(mCurrentPlayerState->GetGameHighScore())));
}
