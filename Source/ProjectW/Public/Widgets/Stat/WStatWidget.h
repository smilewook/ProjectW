// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Widgets/WContentWidgetBase.h"
#include "WStatWidget.generated.h"


class UWStatManager;
class UWStatLabelWidget;

class UButton;
class UTextBlock;
class UVerticalBox;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWStatWidget : public UWContentWidgetBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	virtual void InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager) override;

	void CreateStatAttribute();

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;

private:
	UFUNCTION()
	void OnCloseButtonClicked();

	/* Properties */
protected:
	UPROPERTY()
	UTextBlock* mpNameText;

	UPROPERTY()
	UButton* mpCloseButton;
	
	UPROPERTY()
	UTextBlock* mpDefaultStatText;
	
	UPROPERTY()
	UVerticalBox* mpDefaultStats;

	UPROPERTY()
	UTextBlock* mpSpecialStatText;

	UPROPERTY()
	UVerticalBox* mpSpecialStats;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWStatLabelWidget> mStatLabelWidgetClass;

	UWStatManager* mpStatManager;
};
