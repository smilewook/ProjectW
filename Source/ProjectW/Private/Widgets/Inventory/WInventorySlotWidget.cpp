// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventorySlotWidget.h"
#include "ProjectWStructure.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"

#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>


void UWInventorySlotWidget::InitWidget(UWInventoryManager* pInventory, FInventorySlotInfo* pSlotInfo)
{
	WCHECK(nullptr != pInventory);
	if (nullptr != pInventory)
	{
		mpInventory = pInventory;
	}
	WCHECK(nullptr != pSlotInfo);
	if (nullptr != pSlotInfo)
	{
		mpSlotInfo = pSlotInfo;
		mpSlotInfo->pSlotWidget = this;
	}
}

void UWInventorySlotWidget::UpdateWidget()
{
	if (nullptr != mpSlotInfo)
	{
		if (nullptr != mpSlotInfo->pItemClass)
		{
			mpIcon->SetBrushFromTexture(mpSlotInfo->pItemClass->GetItemInfo().pIcon);

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
			mpIcon->SetBrushFromTexture(nullptr);
			mpAmountText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UWInventorySlotWidget::Show()
{
	mpIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	mpAmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWInventorySlotWidget::Hide()
{
	mpIcon->SetVisibility(ESlateVisibility::Hidden);
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
	// �巡�� ����
}

bool UWInventorySlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
 	// ��� �Ǿ�����
	return false;
}

void UWInventorySlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// ���콺 ����
}

void UWInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// ���콺 �ƿ�
}

void UWInventorySlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �巡�� ����
}

void UWInventorySlotWidget::NativeOnDragLeave(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// �巡�� �ƿ�
}
