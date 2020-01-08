// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WAcquireItemWidget.generated.h"


class AWItemBase;
class UBorder;
class UImage;
class UTextBlock;
class UWidgetAnimation;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWAcquireItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	void InitWidget(AWItemBase* pItemClass, int amount, float visibleDuration, class UWMainWidget* pMainWidget);

	UFUNCTION()
	void Show();
	UFUNCTION()
	void Hide();

	/* Get */
	FORCEINLINE UTextBlock* const& GetAmount()   const { return mpAmountText; }
	FORCEINLINE UTextBlock* const& GetName()     const { return mpNameText; }
	FORCEINLINE UImage*     const& GetIcon()     const { return mpIcon; }

protected:
	void AssignAnimations();

	UFUNCTION()
	void FadeIn();
	UFUNCTION()
	void FadeOut();

	/* Properties */
protected:
	UPROPERTY()
	UImage* mpIcon;

	UPROPERTY()
	UTextBlock* mpNameText;

	UPROPERTY()
	UTextBlock* mpAmountText;

	UWidgetAnimation* mpFadeOut;
	UWidgetAnimation* mpFadeIn;

	AWItemBase* mpItemClass;

	int32 mAmount;

	float mVisibleDuration;

	UWMainWidget* mpMainWidget;

	
};
