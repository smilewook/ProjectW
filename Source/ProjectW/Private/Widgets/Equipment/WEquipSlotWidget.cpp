// Fill out your copyright notice in the Description page of Project Settings.


#include "WEquipSlotWidget.h"
#include "WSlotDragDropOperation.h"
#include "Items/WItemEquipment.h"
#include "Managers/WEquipmentManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"

#include <Components/Border.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>


void UWEquipSlotWidget::InitWidget(UWEquipmentManager* pEquipmentManager, FEquipmentSlotInfo* pSlotInfo)
{
	WCHECK(nullptr != mpEquipmentManager);
	if (nullptr != mpEquipmentManager)
	{
		mpEquipmentManager = pEquipmentManager;
	}
	WCHECK(nullptr != pSlotInfo);
	if (nullptr != pSlotInfo)
	{
		mpSlotInfo = pSlotInfo;
	}
}

void UWEquipSlotWidget::UpdateWidget()
{
	if (nullptr != mpSlotInfo)
	{
		if (nullptr != mpSlotInfo->pItemClass)
		{
			mpIcon->SetBrushFromTexture(mpSlotInfo->pItemClass->GetItemInfo().pIcon);
		}
		else
		{
			SetToolTip(nullptr);
			mpIcon->SetBrushFromTexture(nullptr);
		}
	}
}

void UWEquipSlotWidget::Show()
{
	mpIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWEquipSlotWidget::Hide()
{
	mpIcon->SetVisibility(ESlateVisibility::Hidden);
}

void UWEquipSlotWidget::NativeConstruct()
{
	mOnColor = FLinearColor(1.0f, 1.0f, 1.0f);
	mOverColor = FLinearColor(0.9f, 0.3f, 0.0f);
	mNoEquipColor = FLinearColor(1.0f, 0.0f, 0.0f);
	mpOutline->SetBrushColor(mOnColor);

	mpBackground->SetBrushFromTexture(mpBackgroundImage);
}

FReply UWEquipSlotWidget::NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	if (nullptr != mpSlotInfo->pItemClass)
	{
		// ���콺 ���� Ŭ��.
		if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			FReply result(FReply::Handled());

			result.DetectDrag(this->TakeWidget(), EKeys::LeftMouseButton);
			return result;
		}

		// ���콺 ������ Ŭ��.
		if (inMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			// ��� Ż�� to �κ��丮.
			//mpEquipmentManager->getmpSlotInfo->pItemClass->GetItemEquipType()

			return FReply::Handled();
		}
	}

	return FReply::Handled();
}

void UWEquipSlotWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	// �巡�� ����. SlotDragDropOperation ����.
	UWSlotDragDropOperation* pSlotOperation = NewObject<UWSlotDragDropOperation>(UWSlotDragDropOperation::StaticClass());
	pSlotOperation->SetDraggedSlot(this);
	pSlotOperation->DefaultDragVisual = this;
	pSlotOperation->Pivot = EDragPivot::MouseDown;

	outOperation = pSlotOperation;
}

bool UWEquipSlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// ��� �Ǿ�����
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		AWItemEquipment* pItemEquipment = Cast<AWItemEquipment>(pFromSlot->GetSlotInfo()->pItemClass);
		if (pItemEquipment->GetItemEquipType() == mItemEquipType)
		{
			// ��� ���� from �κ��丮.
			pFromSlot->GetSlotInfo()->pItemClass = nullptr;
			pFromSlot->GetSlotInfo()->Amount = 0;
			pFromSlot->GetSlotInfo()->pSlotWidget->UpdateWidget();

			return true;
		}
	}
	return false;
}

void UWEquipSlotWidget::NativeOnDragCancelled(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �� �������� ����ɶ� ȣ��ǳ�..
	WLOG(Warning, TEXT("drop cancelled!"));

	if (nullptr != mpSlotInfo)
	{
		// ��� Ż�� to �κ��丮.
	}
}

void UWEquipSlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// ���콺 ����
	mpOutline->SetBrushColor(mOverColor);
}

void UWEquipSlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// ���콺 �ƿ�
	mpOutline->SetBrushColor(mOnColor);
}

void UWEquipSlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �巡�� ����
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		// ��� ������ ���� �ƴ� ��츦 ����.
		mpOutline->SetBrushColor(mOverColor);
	}
}

void UWEquipSlotWidget::NativeOnDragLeave(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �巡�� �ƿ�
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		mpOutline->SetBrushColor(mOnColor);
	}
}
