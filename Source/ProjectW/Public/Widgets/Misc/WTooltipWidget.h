// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Widgets/WContentWidgetBase.h"
#include "WTooltipWidget.generated.h"


class AWItemBase;
class UWMainWidget;
class UImage;
class UTextBlock;
class UVerticalBox;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWTooltipWidget : public UWContentWidgetBase
{
	GENERATED_BODY()
	
	/* Method */
public:
	virtual void InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager) override;

	void UpdateData(AWItemBase* pItemClass);

protected:
	

	/* Properties */
private:
	UPROPERTY()
	UWMainWidget* mpMainWidget;

	UPROPERTY()
	UImage* mpIcon;

	UPROPERTY()
	UTextBlock* mpNameText;

	UPROPERTY()
	UTextBlock* mpDescriptionText;

	UPROPERTY()
	UVerticalBox* mpStatSection;

	UPROPERTY()
	UVerticalBox* mpStats;
};
