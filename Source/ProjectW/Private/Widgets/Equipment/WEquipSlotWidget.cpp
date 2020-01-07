// Fill out your copyright notice in the Description page of Project Settings.


#include "WEquipSlotWidget.h"
#include "DragDropOperation/WSlotDragDropOperation.h"
#include "Items/WItemEquipment.h"
#include "Managers/WEquipmentManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"
#include "Widgets/Misc/WTooltipWidget.h"

#include <Components/Border.h>
#include <Components/Image.h>


void UWEquipSlotWidget::InitWidget(UWEquipmentManager* pEquipmentManager, const FEquipmentSlotInfo* const& pSlotInfo)
{
	mpEquipmentManager = pEquipmentManager;

	mpSlotInfo = pSlotInfo;
}

void UWEquipSlotWidget::UpdateWidget()
{
	if (nullptr != mpSlotInfo)
	{
		if (nullptr != mpSlotInfo->pItemClass)
		{
			mpIcon->SetBrushFromTexture(mpSlotInfo->pItemClass->GetItemInfo().pIcon);
			mpIcon->SetRenderOpacity(1.0f);
		}
		else
		{
			mpIcon->SetBrushFromTexture(nullptr);
			mpIcon->SetRenderOpacity(0.0f);

			SetToolTip(nullptr);
		}
	}
}

void UWEquipSlotWidget::Show()
{
	if (nullptr != mpSlotInfo->pItemClass)
	{
		UTexture2D* pIcon = mpSlotInfo->pItemClass->GetItemInfo().pIcon;
		mpIcon->SetBrushFromTexture(pIcon);
		mpIcon->SetRenderOpacity(1.0f);
	}
}

void UWEquipSlotWidget::Hide()
{
	mpIcon->SetBrushFromTexture(nullptr);
	mpIcon->SetRenderOpacity(0.0f);

	SetToolTip(nullptr);
}

void UWEquipSlotWidget::NativePreConstruct()
{
	WCHECK(nullptr != mpOutline);

	mOnColor = FLinearColor(1.0f, 1.0f, 1.0f);
	mOverColor = FLinearColor(0.9f, 0.3f, 0.0f);
	mFailColor = FLinearColor(0.5f, 0.0f, 0.0f);
	mpOutline->SetBrushColor(mOnColor);
	mpBackground->SetBrushFromTexture(mpBackgroundImage);

	//WLOG(Warning, TEXT("UWEquipSlotWidget::NativePreConstruct()"));
}

FReply UWEquipSlotWidget::NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	if (nullptr != mpSlotInfo->pItemClass)
	{
		// ���콺 ������ Ŭ��.
		if (inMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			// ��� Ż�� to �κ��丮.
			mpEquipmentManager->UnequipSlot(mpSlotInfo->pItemClass);

			return FReply::Handled();
		}
	}

	return FReply::Handled();
}

void UWEquipSlotWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
 	// �巡�׷� �׼��� ��� �������� �����ϱ�.
}

bool UWEquipSlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// ��� �Ǿ�����
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		AWItemEquipment* pItemEquipment = Cast<AWItemEquipment>(pFromSlot->GetSlotInfo()->pItemClass);
		if (nullptr != pItemEquipment)
		{
			if (pItemEquipment->GetItemEquipType() == mItemEquipType)
			{
				// ��� ���� from �κ��丮.
				bool bSuccess = mpEquipmentManager->EquipSlot(pItemEquipment);
				if (true == bSuccess)
				{
					pFromSlot->GetSlotInfo()->pItemClass = nullptr;
					pFromSlot->GetSlotInfo()->Amount = 0;
					pFromSlot->GetSlotInfo()->pSlotWidget->UpdateWidget();
				}

				return true;
			}
		}		
	}
	return false;
}

void UWEquipSlotWidget::NativeOnDragCancelled(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �� �������� ����ɶ� ȣ��ǳ�..
	WLOG(Warning, TEXT("drop cancelled!"));

	mpOutline->SetBrushColor(mOnColor);
}

void UWEquipSlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// ���콺 ����
	mpOutline->SetBrushColor(mOverColor);

	if (nullptr != mpSlotInfo->pItemClass && nullptr != mpTooltipWidget)
	{
		mpTooltipWidget->UpdateData(mpSlotInfo->pItemClass);
		SetToolTip(mpTooltipWidget);
	}
}

void UWEquipSlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// ���콺 �ƿ�
	mpOutline->SetBrushColor(mOnColor);

	SetToolTip(nullptr);
}

void UWEquipSlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �巡�� ����
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		// ��� ������ ���� �ƴ� ��츦 ����.
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		AWItemEquipment* pItemEquipment = Cast<AWItemEquipment>(pFromSlot->GetSlotInfo()->pItemClass);
		if (nullptr != pItemEquipment)
		{
			if (pItemEquipment->GetItemEquipType() == mItemEquipType)
			{
				mpOutline->SetBrushColor(mOverColor);
				return;
			}
		}
		mpOutline->SetBrushColor(mFailColor);
		return;
	}
}

void UWEquipSlotWidget::NativeOnDragLeave(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �巡�� �ƿ�
	mpOutline->SetBrushColor(mOnColor);
}
