// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventorySlotWidget.h"
#include "ProjectWStructure.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/WInventorySlotWidget.h"

#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>


bool UWInventorySlotWidget::InitWidget(UWInventoryManager* pInventory, FInventorySlotInfo* pSlotInfo)
{
	if (nullptr != pInventory)
	{
		mpInventory = pInventory;
	}

	if (nullptr != pSlotInfo)
	{
		mpSlotInfo = pSlotInfo;
	}

	return true;
}

void UWInventorySlotWidget::UpdateWidget()
{
	if (nullptr != mpSlotInfo)
	{
		if (nullptr != mpSlotInfo->pItemClass)
		{
			mpItemIcon->SetBrushFromTexture(mpSlotInfo->pItemClass->GetItemInfo().pItemIcon);

			if (mpSlotInfo->pItemClass->GetItemInfo().IsStackAble && (mpSlotInfo->Amount > 0))
			{
				mpAmountText->SetText(FText::AsNumber(mpSlotInfo->Amount));
				mpAmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				mpAmountText->SetText(FText::AsNumber(0));
				mpAmountText->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			SetToolTip(nullptr);
			mpItemIcon->SetBrushFromTexture(nullptr);
			mpAmountText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UWInventorySlotWidget::Show()
{
	mpItemIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	mpAmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWInventorySlotWidget::Hide()
{
	mpItemIcon->SetVisibility(ESlateVisibility::Hidden);
	mpAmountText->SetVisibility(ESlateVisibility::Hidden);
}

FReply UWInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	if (mpSlotInfo->pItemClass)
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
			if (mpSlotInfo->pItemClass->GetItemInfo().IsUseAble)
			{
				if (mpSlotInfo->pItemClass->OnUse(mpSlotInfo))
				{
					UpdateWidget();
				}
			}

			return FReply::Handled();
		}
	}

	return FReply::Handled();
}

void UWInventorySlotWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	// DragDrop ���� ����.
// 	UOperation_Slot* pOper_Slot = NewObject<UOperation_Slot>(UOperation_Slot::StaticClass());
// 	pOper_Slot->InitOperation(this);
// 	pOper_Slot->DefaultDragVisual = this;
// 	pOper_Slot->Pivot = EDragPivot::MouseDown;
// 
// 	OutOperation = pOper_Slot;
}

bool UWInventorySlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
// 	if (UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation))
// 	{
// 		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pOper_Slot->GetDraggedSlot());
// 		FInventorySlotInfo* pFromSlotInfo = pFromSlot->GetSlotInfo();
// 		if (nullptr != mpSlotInfo->pItemClass)
// 		{
// 			// ������ �̵�
// 			mpInventory->MoveItem(mpSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
// 		}
// 		else
// 		{
// 			if ((pFromSlot != this) && (mpSlotInfo->pItemClass->GetClass() == pFromSlotInfo->pItemClass->GetClass()))
// 			{
// 				// ������ ��ġ��(����)
// 				mpInventory->CombineItem(mpSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
// 			}
// 			else
// 			{
// 				// ������ ����
// 				mpInventory->SwapItem(mpSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
// 			}
// 		}
// 		return true;
// 	}
	return false;
}

void UWInventorySlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
// 	if (mpSlotInfo->pItemClass && mpDetailWidget)
// 	{
// 		// ���� ���콺 ���� ����
// 		mpDetailWidget->UpdateWidget(mpSlotInfo->pItemClass->GetClass());
// 		SetToolTip(mpDetailWidget);
// 	}
}

void UWInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
// 	if (mpSlotInfo->pItemClass && mpDetailWidget)
// 	{
// 		// ���� ���콺 �ƿ�(�⺻) ����
// 		SetToolTip(nullptr);
// 	}
}

void UWInventorySlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
// 	if (UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation))
// 	{
// 		// ���� �巡�� ���� ����
// 	}
}

void UWInventorySlotWidget::NativeOnDragLeave(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
// 	if (UOperation_Slot* pOper_Slot = Cast<UOperation_Slot>(InOperation))
// 	{
// 		// ���� �巡�� �ƿ�(�⺻) ����
// 	}
}
