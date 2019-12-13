// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WHUDWidget.generated.h"


class AWPlayerState;
class UWCharacterStatComponent;
class UWMainWidget;

class UProgressBar;
class UTextBlock;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Method */
public:
	void InitWidget(UWMainWidget* pMainWidget);
	void BindCharacterStat(UWCharacterStatComponent* pCharacterStat);
	void BindPlayerState(AWPlayerState* pPlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

	/* Properties */
private:
	TWeakObjectPtr<UWCharacterStatComponent> mCurrentCharacterStat;
	TWeakObjectPtr<AWPlayerState> mCurrentPlayerState;

	UPROPERTY()
	UWMainWidget* mpMainWidget;

	UPROPERTY()
	UProgressBar* mpHPBar;

	UPROPERTY()
	UProgressBar* mpExpBar;

	UPROPERTY()
	UTextBlock* mpPlayerName;

	UPROPERTY()
	UTextBlock* mpPlayerLevel;

	UPROPERTY()
	UTextBlock* mpCurrentScore;

	UPROPERTY()
	UTextBlock* mpHighScore;
};
