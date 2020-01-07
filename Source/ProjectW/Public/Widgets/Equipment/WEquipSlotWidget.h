// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "ProjectWEnums.h"
#include "WEquipSlotWidget.generated.h"


class AWItemEquipment;
class UWEquipmentManager;
class UWTooltipWidget;
class UBorder;
class UImage;
class UTexture2D;

struct FEquipmentSlotInfo;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWEquipSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
		/* Methods */
public:
	void InitWidget(UWEquipmentManager* pEquipmentManager, const FEquipmentSlotInfo* const& pSlotInfo);
	void UpdateWidget();

	void Show();
	void Hide();

	/* Get/Set */
	FORCEINLINE const EItemEquipType& GetItemEquipType() const { return mItemEquipType; }

	FORCEINLINE void SetTooltipWidget(UWTooltipWidget* pTooltipWidget) { mpTooltipWidget = pTooltipWidget; }
	
protected:
	virtual void NativePreConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;
	virtual bool NativeOnDrop(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation);
	virtual void NativeOnMouseEnter(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragEnter(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;

	/* Properties */
public:

protected:
	UPROPERTY()
	UBorder* mpOutline;

	UPROPERTY()
	UBorder* mpBackground;

	UPROPERTY()
	UImage* mpIcon;

	UPROPERTY(EditAnywhere, Category = "Configuration | EquipType")
	EItemEquipType mItemEquipType;

	UPROPERTY(EditAnywhere, Category = "Configuration | Outline")
	FLinearColor mOnColor;

	UPROPERTY(EditAnywhere, Category = "Configuration | Outline")
	FLinearColor mOverColor;

	UPROPERTY(EditAnywhere, Category = "Configuration | Outline")
	FLinearColor mFailColor;

	UPROPERTY(EditAnywhere, Category = "Configuration | Background")
	UTexture2D* mpBackgroundImage;

	const FEquipmentSlotInfo* mpSlotInfo = nullptr;	

	UWEquipmentManager* mpEquipmentManager;	

	UWTooltipWidget* mpTooltipWidget = nullptr;
	
};
