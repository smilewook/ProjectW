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
			// 장비 탈착 to 인벤토리.
			//mpEquipmentManager->getmpSlotInfo->pItemClass->GetItemEquipType()

			return FReply::Handled();
		}
	}

	return FReply::Handled();
}

void UWEquipSlotWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	// 드래그 시작. SlotDragDropOperation 생성.
	UWSlotDragDropOperation* pSlotOperation = NewObject<UWSlotDragDropOperation>(UWSlotDragDropOperation::StaticClass());
	pSlotOperation->SetDraggedSlot(this);
	pSlotOperation->DefaultDragVisual = this;
	pSlotOperation->Pivot = EDragPivot::MouseDown;

	outOperation = pSlotOperation;
}

bool UWEquipSlotWidget::NativeOnDrop(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드랍 되었을때
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		AWItemEquipment* pItemEquipment = Cast<AWItemEquipment>(pFromSlot->GetSlotInfo()->pItemClass);
		if (pItemEquipment->GetItemEquipType() == mItemEquipType)
		{
			// 장비 장착 from 인벤토리.
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
	// 빈 영역으로 드랍될때 호출되네..
	WLOG(Warning, TEXT("drop cancelled!"));

	if (nullptr != mpSlotInfo)
	{
		// 장비 탈착 to 인벤토리.
	}
}

void UWEquipSlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// 마우스 오버
	mpOutline->SetBrushColor(mOverColor);
}

void UWEquipSlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// 마우스 아웃
	mpOutline->SetBrushColor(mOnColor);
}

void UWEquipSlotWidget::NativeOnDragEnter(const FGeometry & inGeometry, const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드래그 오버
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		// 드랍 가능한 경우와 아닌 경우를 구분.
		mpOutline->SetBrushColor(mOverColor);
	}
}

void UWEquipSlotWidget::NativeOnDragLeave(const FDragDropEvent & inDragDropEvent, UDragDropOperation * inOperation)
{
	// 드래그 아웃
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		mpOutline->SetBrushColor(mOnColor);
	}
}
