// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Widgets/WContentWidgetBase.h"
#include "WLootingWidget.generated.h"


class UButton;
class UTextBlock;
class UVerticalBox;
class UWLootingSlotWidget;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWLootingWidget : public UWContentWidgetBase
{
	GENERATED_BODY()
	
		/* Methods */
public:
	bool CreateSlots();
	void RemoveSlots();

	/* Get/Set */

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;

private:
	UFUNCTION()
	void OnCloseButtonClicked();

	/* Properties */
public:

protected:
	UPROPERTY()
	UTextBlock* mpNameText;
	
	UPROPERTY()
	UButton* mpCloseButton;
	
	UPROPERTY()
	UVerticalBox* mpLootingSlots;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWLootingSlotWidget> mSlotWidgetClass;
};
