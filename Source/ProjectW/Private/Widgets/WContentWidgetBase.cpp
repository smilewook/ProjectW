// Fill out your copyright notice in the Description page of Project Settings.


#include "WContentWidgetBase.h"
#include "Widgets/WMainWidget.h"
#include "WContentsDragDropOperation.h"


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

	// 스크린에서의 절대 좌료(마우스 위치) 구하기.
	FVector2D mousePos = inMouseEvent.GetScreenSpacePosition();

	// 절대 좌표(마우스 위치)를 (Geometry)로컬 좌표로 변환.
	FVector2D localPos = inGeometry.AbsoluteToLocal(mousePos);	// 위젯 DragDropOperation 생성.
	UWContentsDragDropOperation* pWidgetOperation = NewObject<UWContentsDragDropOperation>(UWContentsDragDropOperation::StaticClass());
	pWidgetOperation->InitOperation(mpMainWidget, this, localPos);
	pWidgetOperation->DefaultDragVisual = this;
	pWidgetOperation->Pivot = EDragPivot::MouseDown;

	// 현재 위젯 제거.
	RemoveFromParent();

	outOperation = pWidgetOperation;
	//WLOG(Warning, TEXT("UWInventorySlotWidget::NativeOnDragDetected()"));
}
