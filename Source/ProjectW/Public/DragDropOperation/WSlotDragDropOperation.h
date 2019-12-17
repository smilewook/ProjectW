// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/DragDropOperation.h"
#include "WSlotDragDropOperation.generated.h"


class UWInventorySlotWidget;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWSlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
	/* Methods */
public:

	/* Get/Set */
	FORCEINLINE UWInventorySlotWidget* const& GetDraggedSlot() const { return mpDraggerSlot; }

	FORCEINLINE void SetDraggedSlot(UWInventorySlotWidget* const& pDraggedSlot) { mpDraggerSlot = pDraggedSlot; }

	/* Properties */
protected:
	UWInventorySlotWidget* mpDraggerSlot;

};
