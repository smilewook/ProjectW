// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Widgets/WContentWidgetBase.h"
#include "WEquipmentWidget.generated.h"


class UWEquipSlotWidget;

class UButton;
class UTextBlock;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWEquipmentWidget : public UWContentWidgetBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	virtual void InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager) override;

	/* Get/Set */
	FORCEINLINE UWEquipSlotWidget* const& GetEquipSlotByItemEquipType(EItemEquipType itemEquipType) const;

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
	
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf <UWEquipSlotWidget> mSlotWidgetClass;

	UPROPERTY()
	UWEquipSlotWidget* mpWeaponSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpShieldSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpHeadSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpShoulderSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpTopSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpBottomSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpGloveSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpNecklaceSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpEarringSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpRingSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpBraceletSlot;

	UPROPERTY()
	UWEquipSlotWidget* mpDummySlot;
};
