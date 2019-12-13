// Fill out your copyright notice in the Description page of Project Settings.


#include "WHUDWidget.h"
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

	mpHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	WCHECK(nullptr != mpHPBar);

	mpExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	WCHECK(nullptr != mpExpBar);

	mpPlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	WCHECK(nullptr != mpPlayerName);

	mpPlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	WCHECK(nullptr != mpPlayerLevel);

	mpCurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	WCHECK(nullptr != mpCurrentScore);

	mpHighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	WCHECK(nullptr != mpHighScore);
}

void UWHUDWidget::UpdateCharacterStat()
{
	WCHECK(mCurrentCharacterStat.IsValid());

	mpHPBar->SetPercent(mCurrentCharacterStat->GetHPRatio());
}

void UWHUDWidget::UpdatePlayerState()
{
	WCHECK(mCurrentPlayerState.IsValid());

	mpExpBar->SetPercent(mCurrentPlayerState->GetExpRatio());
	mpPlayerName->SetText(FText::FromString(mCurrentPlayerState->GetPlayerName()));
	mpPlayerLevel->SetText(FText::FromString((FString::FromInt(mCurrentPlayerState->GetCharacterLevel()))));
	mpCurrentScore->SetText(FText::FromString((FString::FromInt(mCurrentPlayerState->GetGameScore()))));
	mpHighScore->SetText(FText::FromString(FString::FromInt(mCurrentPlayerState->GetGameHighScore())));
}
