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
		// ��ũ�� ������ ���콺 ��ġ.	
		FVector2D mousePos = pointerEvent.GetScreenSpacePosition();

		// ���� ��ǥ(��ũ�� ����)�� ���� ��ǥ(���� ����)�� ��ȯ.
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
		// ��ũ�� ������ ���콺 ��ġ.	
		FVector2D mousePos = pointerEvent.GetScreenSpacePosition();

		// ���� ��ǥ(��ũ�� ����)�� ���� ��ǥ(���� ����)�� ��ȯ.
		FVector2D localPos = mpMainWidget->GetCachedGeometry().AbsoluteToLocal(mousePos);

		FVector2D resultPos = localPos - mOffset;

		mpDraggedWidget->AddToViewport();
		mpDraggedWidget->SetPositionInViewport(resultPos, false);
	}
}

void UWContentsDragDropOperation::Dragged_Implementation(const FPointerEvent & pointerEvent)
{
}
