// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/DragDropOperation.h"
#include "WContentsDragDropOperation.generated.h"


class UWContentWidgetBase;
class UWMainWidget;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWContentsDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
	/* Methods */
public:
	void InitOperation(UWMainWidget* pMainWidget, UUserWidget* pDraggedWidget, const FVector2D& offset);

	void Drop_Implementation(const FPointerEvent& pointerEvent);
	void DragCancelled_Implementation(const FPointerEvent& pointerEvent);
	void Dragged_Implementation(const FPointerEvent& pointerEvent);

	/* Get/Set */
	FORCEINLINE UUserWidget* const& GetDraggedWidget() const { return mpDraggedWidget; }
	FORCEINLINE const FVector2D& GetOffset() const { return mOffset; }

	/* Properties */
protected:
	UUserWidget* mpDraggedWidget;
	FVector2D mOffset;
	
	UWMainWidget* mpMainWidget;

};
