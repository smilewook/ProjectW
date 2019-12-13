// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WInventorySlotWidget.generated.h"


class UWInventoryManager;
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
	bool InitWidget(UWInventoryManager* pInventory, FInventorySlotInfo* pSlotInfo);
	void UpdateWidget();

	void Show();
	void Hide();

	/* Get/Set */
	FORCEINLINE FInventorySlotInfo* const& GetSlotInfo() const { return mpSlotInfo; }
	//FORCEINLINE UWidget_HotkeySlot* const& GetHotkeySlotWidget() const { return m_pHotkeySlotWidget; }

	//FORCEINLINE void SetHotkeySlotWidget(UWidget_HotkeySlot* _pWidget) { m_pHotkeySlotWidget = _pWidget; }

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;
	virtual bool NativeOnDrop(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragEnter(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;

	/* Properties */
public:

protected:
	UPROPERTY()
	class UButton* mpButton;

	UPROPERTY()
	class UImage* mpItemIcon;

	UPROPERTY()
	class UTextBlock* mpAmountText;

	UWInventoryManager* mpInventory;

	FInventorySlotInfo* mpSlotInfo = nullptr;
};
