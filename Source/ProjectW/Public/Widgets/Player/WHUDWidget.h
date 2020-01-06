// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WHUDWidget.generated.h"


class AWPlayerState;
class UWMainWidget;
class UWStatManager;
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
	void BindCharacterStat(UWStatManager* pStatManager);
	void BindPlayerState(AWPlayerState* pPlayerState);

protected:
	void UpdatePlayerHP();
	void UpdatePlayerMP();
	void UpdatePlayerState();

	/* Properties */
private:	
	UPROPERTY()
	UWMainWidget* mpMainWidget;

	UPROPERTY()
	UWStatManager* mpStatManager;

	UPROPERTY()
	AWPlayerState* mpPlayerState;

	UPROPERTY()
	UProgressBar* mpHPProgressBar;

	UPROPERTY()
	UProgressBar* mpMPProgressBar;

	UPROPERTY()
	UTextBlock* mpNameText;

	UPROPERTY()
	UTextBlock* mpLevelText;
};
