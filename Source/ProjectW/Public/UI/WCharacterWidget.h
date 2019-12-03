// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API UWCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Method */
public:
	void BindCharacterStat(class UWCharacterStatComponent* pNewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
	
	/* Properties */
private:
	TWeakObjectPtr<class UWCharacterStatComponent> mCurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* mpHPProgressBar;
};
