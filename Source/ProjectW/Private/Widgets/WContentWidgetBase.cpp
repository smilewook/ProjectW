// Fill out your copyright notice in the Description page of Project Settings.


#include "WContentWidgetBase.h"
#include "Widgets/WMainWidget.h"


void UWContentWidgetBase::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	if (nullptr != pMainWidget)
	{
		mpMainWidget = pMainWidget;
	}
	
	if (nullptr != pContentManager)
	{
		mpContentManager = pContentManager;
	}
}

void UWContentWidgetBase::UpdateWidget()
{

}

FReply UWContentWidgetBase::NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	Super::NativeOnMouseButtonDown(inGeometry, inMouseEvent);

	FReply result(FReply::Handled());
	result.DetectDrag(this->TakeWidget(), EKeys::LeftMouseButton);
	return result;
}

void UWContentWidgetBase::NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation)
{
	Super::NativeOnDragDetected(inGeometry, inMouseEvent, outOperation);

	// ��ũ�������� ���� �·�(���콺 ��ġ) ���ϱ�.
	FVector2D mousePos = inMouseEvent.GetScreenSpacePosition();

	// ���� ��ǥ(���콺 ��ġ)�� (Geometry)���� ��ǥ�� ��ȯ.
	FVector2D localPos = inGeometry.AbsoluteToLocal(mousePos);
}
