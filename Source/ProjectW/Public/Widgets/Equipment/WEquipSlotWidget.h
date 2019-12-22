// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Blueprint/UserWidget.h"
#include "WEquipSlotWidget.generated.h"


class UWEquipmentManager;
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
	void InitWidget(UWEquipmentManager* pEquipment, FEquipmentSlotInfo* pSlotInfo);
	void UpdateWidget();

	void Show();
	void Hide();

	/* Get/Set */
	FORCEINLINE FEquipmentSlotInfo* const& GetSlotInfo() const { return mpSlotInfo; }

protected:
	virtual void NativeConstruct() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Appearance")
	FLinearColor mOnColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Appearance")
	FLinearColor mOverColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Appearance")
	FLinearColor mNoEquipColor;

	UPROPERTY()
	UBorder* mpBackground;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Appearance")
	UTexture2D* mpBackgroundImage;

	UPROPERTY()
	UImage* mpIcon;

	FEquipmentSlotInfo* mpSlotInfo = nullptr;

	UWEquipmentManager* mpEquipmentManager;

private:
	EItemEquipType mItemEquipType;
};
