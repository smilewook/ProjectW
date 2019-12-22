// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WInventorySlotWidget.generated.h"


class UWInventoryManager;
class UWItemDestroyWidget;

struct FInventorySlotInfo;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	void InitWidget(UWInventoryManager* pInventory, FInventorySlotInfo* pSlotInfo);
	void UpdateWidget();

	void Show();
	void Hide();

	/* Get/Set */
	FORCEINLINE FInventorySlotInfo* const& GetSlotInfo() const { return mpSlotInfo; }

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
	UPROPERTY(BlueprintReadOnly)
	class UBorder* mpOutline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Appearance")
	FLinearColor mOnColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration | Appearance")
	FLinearColor mOverColor;

	UPROPERTY()
	class UImage* mpIcon;

	UPROPERTY()
	class UTextBlock* mpAmountText;

	FInventorySlotInfo* mpSlotInfo = nullptr;

	UWInventoryManager* mpInventoryManager;

	UWItemDestroyWidget* mpItemDestroy;
};
