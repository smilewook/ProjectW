// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventorySlotWidget.h"
#include "ProjectWStructure.h"
#include "WSlotDragDropOperation.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"

#include <Components/Border.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>


void UWInventorySlotWidget::InitWidget(UWInventoryManager* pInventoryManager, FInventorySlotInfo* pSlotInfo)
{
	WCHECK(nullptr != pInventoryManager);
	if (nullptr != pInventoryManager)
	{
		mpInventoryManager = pInventoryManager;
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

void UWInventorySlotWidget::NativeConstruct()
{
	mOnColor = FLinearColor(1.0f, 1.0f, 1.0f);
	mOverColor = FLinearColor(0.9f, 0.3f, 0.0f);

	mpOutline->SetBrushColor(mOnColor);
}

FReply UWInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
{
	if (nullptr != mpSlotInfo->pItemClass)
	{
		// 마우스 왼쪽 클릭.
		if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			FReply result(FReply::Handled());

			result.DetectDrag(this->TakeWidget(), EKeys::LeftMouseButton);
			return result;
		}

		// 마우스 오른쪽 클릭.
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
	// 드래그 시작. SlotDragDropOperation 생성.
	UWSlotDragDropOperation* pSlotOperation = NewObject<UWSlotDragDropOperation>(UWSlotDragDropOperation::StaticClass());
	pSlotOperation->SetDraggedSlot(this);
	pSlotOperation->DefaultDragVisual = this;
	pSlotOperation->Pivot = EDragPivot::MouseDown;

	outOperation = pSlotOperation;
}

bool UWInventorySlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
 	// 드랍 되었을때
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		FInventorySlotInfo* pFromSlotInfo = pFromSlot->GetSlotInfo();
		if (nullptr == mpSlotInfo->pItemClass)
		{
			mpInventoryManager->MoveItem(mpSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
		}
		else
		{
			if ((pFromSlot != this) && (mpSlotInfo->pItemClass->GetItemID() == pFromSlotInfo->pItemClass->GetItemID()))
			{
				mpInventoryManager->CombineItem(mpSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
			}
			else if (pFromSlot == this)
			{
				return true;
			}
			else
			{
				mpInventoryManager->SwapItem(mpSlotInfo->SlotIndex, pFromSlotInfo->SlotIndex);
			}
		}
		return true;
	}
	return false;
}

void UWInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 빈 영역으로 드랍될때 호출되네..
	WLOG(Warning, TEXT("drop cancelled!"));

	if (nullptr != mpSlotInfo)
	{
		mpInventoryManager->ThrowAwayItem(mpSlotInfo->SlotIndex);
	}	
}

void UWInventorySlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// 마우스 오버
	mpOutline->SetBrushColor(mOverColor);
}

void UWInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// 마우스 아웃
	mpOutline->SetBrushColor(mOnColor);
}

void UWInventorySlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드래그 오버
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		mpOutline->SetBrushColor(mOverColor);
	}
}

void UWInventorySlotWidget::NativeOnDragLeave(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드래그 아웃
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		mpOutline->SetBrushColor(mOnColor);
	}
}
