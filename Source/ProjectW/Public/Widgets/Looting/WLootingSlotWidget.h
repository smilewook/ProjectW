// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WLootingSlotWidget.generated.h"


class UWLootingManager;
class UWTooltipWidget;
class UBorder;
class UImage;
class UTextBlock;

struct FInventorySlotInfo;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWLootingSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
		/* Methods */
public:
	void InitWidget(UWLootingManager* pLootingManager, int32 slotIndex);
	void UpdateWidget();

	void Show();
	void Hide();

	/* Get/Set */
	FORCEINLINE void SetTooltipWidget(UWTooltipWidget* pTooltipWidget) { mpTooltipWidget = pTooltipWidget; }

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& inMouseEvent) override;

	/* Properties */
protected:
	UPROPERTY(BlueprintReadOnly)
	UBorder* mpOutline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Outline")
	FLinearColor mOnColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Outline")
	FLinearColor mOverColor;

	UPROPERTY()
	UImage* mpIcon;

	UPROPERTY()
	UTextBlock* mpAmountText;

	UPROPERTY()
	UTextBlock* mpNameText;

	UWLootingManager* mpLootingManager;

	UWTooltipWidget* mpTooltipWidget = nullptr;

private:
	int32 mSlotIndex;
};
