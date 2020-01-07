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
		// 마우스 오른쪽 클릭.
		if (inMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
		{
			// 장비 탈착 to 인벤토리.
			mpEquipmentManager->UnequipSlot(mpSlotInfo->pItemClass);

			return FReply::Handled();
		}
	}

	return FReply::Handled();
}

void UWEquipSlotWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
 	// 드래그로 액션을 어떻게 할지부터 결정하기.
}

bool UWEquipSlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드랍 되었을때
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		AWItemEquipment* pItemEquipment = Cast<AWItemEquipment>(pFromSlot->GetSlotInfo()->pItemClass);
		if (nullptr != pItemEquipment)
		{
			if (pItemEquipment->GetItemEquipType() == mItemEquipType)
			{
				// 장비 장착 from 인벤토리.
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
	// 빈 영역으로 드랍될때 호출되네..
	WLOG(Warning, TEXT("drop cancelled!"));

	mpOutline->SetBrushColor(mOnColor);
}

void UWEquipSlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// 마우스 오버
	mpOutline->SetBrushColor(mOverColor);

	if (nullptr != mpSlotInfo->pItemClass && nullptr != mpTooltipWidget)
	{
		mpTooltipWidget->UpdateData(mpSlotInfo->pItemClass);
		SetToolTip(mpTooltipWidget);
	}
}

void UWEquipSlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// 마우스 아웃
	mpOutline->SetBrushColor(mOnColor);

	SetToolTip(nullptr);
}

void UWEquipSlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드래그 오버
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		// 드랍 가능한 경우와 아닌 경우를 구분.
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
	// 드래그 아웃
	mpOutline->SetBrushColor(mOnColor);
}
