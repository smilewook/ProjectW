// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API UWHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Method */
public:
	void BindCharacterStat(class UWCharacterStatComponent* pCharacterStat);
	void BindPlayerState(class AWPlayerState* pPlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

	/* Properties */
private:
	TWeakObjectPtr<class UWCharacterStatComponent> mCurrentCharacterStat;
	TWeakObjectPtr<class AWPlayerState> mCurrentPlayerState;

	UPROPERTY()
	class UProgressBar* mHPBar;

	UPROPERTY()
	class UProgressBar* mExpBar;

	UPROPERTY()
	class UTextBlock* mPlayerName;

	UPROPERTY()
	class UTextBlock* mPlayerLevel;

	UPROPERTY()
	class UTextBlock* mCurrentScore;

	UPROPERTY()
	class UTextBlock* mHighScore;
};
