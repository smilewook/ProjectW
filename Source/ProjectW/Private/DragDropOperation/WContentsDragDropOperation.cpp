// Fill out your copyright notice in the Description page of Project Settings.


#include "WContentsDragDropOperation.h"
#include "Widgets/WMainWidget.h"


void UWContentsDragDropOperation::InitOperation(UWMainWidget* pMainWidget, UUserWidget* pDraggedWidget, const FVector2D& offset)
{
	if (nullptr != pMainWidget)
	{
		mpMainWidget = pMainWidget;
	}

	if (nullptr != pDraggedWidget)
	{
		mpDraggedWidget = pDraggedWidget;
	}
	
	mOffset = offset;
}

void UWContentsDragDropOperation::Drop_Implementation(const FPointerEvent & pointerEvent)
{
	if (nullptr != mpMainWidget)
	{
		// 스크린 공간의 마우스 위치.	
		FVector2D mousePos = pointerEvent.GetScreenSpacePosition();

		// 절대 좌표(스크린 공간)를 로컬 좌표(메인 위젯)로 변환.
		FVector2D localPos = mpMainWidget->GetCachedGeometry().AbsoluteToLocal(mousePos);

		FVector2D resultPos = localPos - mOffset;

		mpDraggedWidget->AddToViewport();
		mpDraggedWidget->SetPositionInViewport(resultPos, false);
	}
}

void UWContentsDragDropOperation::DragCancelled_Implementation(const FPointerEvent & pointerEvent)
{
	if (nullptr != mpMainWidget)
	{
		// 스크린 공간의 마우스 위치.	
		FVector2D mousePos = pointerEvent.GetScreenSpacePosition();

		// 절대 좌표(스크린 공간)를 로컬 좌표(메인 위젯)로 변환.
		FVector2D localPos = mpMainWidget->GetCachedGeometry().AbsoluteToLocal(mousePos);

		FVector2D resultPos = localPos - mOffset;

		mpDraggedWidget->AddToViewport();
		mpDraggedWidget->SetPositionInViewport(resultPos, false);
	}
}

void UWContentsDragDropOperation::Dragged_Implementation(const FPointerEvent & pointerEvent)
{
}
