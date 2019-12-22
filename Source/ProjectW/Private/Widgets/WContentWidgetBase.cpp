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

	// ��ũ�������� ���� �·�(���콺 ��ġ) ���ϱ�.
	FVector2D mousePos = inMouseEvent.GetScreenSpacePosition();

	// ���� ��ǥ(���콺 ��ġ)�� (Geometry)���� ��ǥ�� ��ȯ.
	FVector2D localPos = inGeometry.AbsoluteToLocal(mousePos);	// ���� DragDropOperation ����.
	UWContentsDragDropOperation* pWidgetOperation = NewObject<UWContentsDragDropOperation>(UWContentsDragDropOperation::StaticClass());
	pWidgetOperation->InitOperation(mpMainWidget, this, localPos);
	pWidgetOperation->DefaultDragVisual = this;
	pWidgetOperation->Pivot = EDragPivot::MouseDown;

	// ���� ���� ����.
	RemoveFromParent();

	outOperation = pWidgetOperation;
	//WLOG(Warning, TEXT("UWInventorySlotWidget::NativeOnDragDetected()"));
}

FVector2D UWContentWidgetBase::GetWidgetCenterLocation() const
{
	FGeometry geometry = mpMainWidget->GetCachedGeometry();
	//FVector2D position = geometry.AbsoluteToLocal(this->GetCachedGeometry().GetAbsolutePosition()) + this->GetCachedGeometry().GetLocalSize() / 2.0f;

	FVector2D absolutePosition = this->GetCachedGeometry().GetAbsolutePosition();
	FVector2D localPosition = geometry.AbsoluteToLocal(this->GetCachedGeometry().GetAbsolutePosition());
	FVector2D localSize = this->GetCachedGeometry().GetLocalSize();
	WLOG(Warning, TEXT("absolutePosition X : %f, Y : %f"), absolutePosition.X, absolutePosition.Y);
	WLOG(Warning, TEXT("localPosition X : %f, Y : %f"), localPosition.X, localPosition.Y);
	WLOG(Warning, TEXT("localSize X : %f, Y : %f"), localSize.X, localSize.Y);
	return localPosition;
}