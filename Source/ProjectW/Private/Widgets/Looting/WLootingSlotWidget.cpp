// Fill out your copyright notice in the Description page of Project Settings.


#include "WLootingSlotWidget.h"
#include "ProjectWStructure.h"
#include "DragDropOperation/WSlotDragDropOperation.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"
#include "Managers/WLootingManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Misc/WTooltipWidget.h"

#include <Components/Border.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include <WidgetBlueprintLibrary.h>


void UWLootingSlotWidget::InitWidget(UWLootingManager* pLootingManager, int32 slotIndex)
{
	WCHECK(nullptr != pLootingManager);
	if (nullptr != pLootingManager)
	{
		mpLootingManager = pLootingManager;
	}

	const FLootingSlotInfo* pSlotInfo = mpLootingManager->GetItemInfo(slotIndex);
	if (nullptr != pSlotInfo)
	{
		mpIcon->SetBrushFromTexture(pSlotInfo->ItemClass.GetDefaultObject()->GetItemInfo().pIcon);
		mpNameText->SetText(FText::FromName(pSlotInfo->ItemClass.GetDefaultObject()->GetItemInfo().Name));
		mpAmountText->SetText(FText::AsNumber(pSlotInfo->Amount));
	}

	mSlotIndex = slotIndex;
}

void UWLootingSlotWidget::UpdateWidget()
{
	
}

void UWLootingSlotWidget::Show()
{
	mpIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	mpAmountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWLootingSlotWidget::Hide()
{
	mpIcon->SetVisibility(ESlateVisibility::Hidden);
	mpAmountText->SetVisibility(ESlateVisibility::Hidden);

	SetToolTip(nullptr);
}

void UWLootingSlotWidget::NativeConstruct()
{
	mpOutline->SetBrushColor(mOnColor);
}

FReply UWLootingSlotWidget::NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent)
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
		AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (pPlayer)
		{
			const FLootingSlotInfo* pSlotInfo = mpLootingManager->GetItemInfo(mSlotIndex);

			FActorSpawnParameters params;
			params.Owner = pPlayer;
			AWItemBase* pItem = GetWorld()->SpawnActor<AWItemBase>(pSlotInfo->ItemClass, params);

			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(pItem, pSlotInfo->Amount);
			if (true == bSuccess)
			{
				pPlayer->GetInventoryManager()->ShowAcquireItem(pItem, pSlotInfo->Amount);
				mpLootingManager->RemoveItem(mSlotIndex);
			}

			SetVisibility(ESlateVisibility::Collapsed);
		}

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UWLootingSlotWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	// 드래그 시작. SlotDragDropOperation 생성.
	UWSlotDragDropOperation* pSlotOperation = NewObject<UWSlotDragDropOperation>(UWSlotDragDropOperation::StaticClass());
	pSlotOperation->SetDraggedSlot(this);
	pSlotOperation->DefaultDragVisual = this;
	pSlotOperation->Pivot = EDragPivot::MouseDown;

	outOperation = pSlotOperation;
}

void UWLootingSlotWidget::NativeOnMouseEnter(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	// 마우스 오버
	mpOutline->SetBrushColor(mOverColor);

	if (nullptr != mpLootingManager->GetItemInfo(mSlotIndex)->ItemClass && nullptr != mpTooltipWidget)
	{
		mpTooltipWidget->UpdateData(mpLootingManager->GetItemInfo(mSlotIndex)->ItemClass.GetDefaultObject());
		SetToolTip(mpTooltipWidget);
	}
}

void UWLootingSlotWidget::NativeOnMouseLeave(const FPointerEvent & inMouseEvent)
{
	// 마우스 아웃
	mpOutline->SetBrushColor(mOnColor);

	if (nullptr != mpLootingManager->GetItemInfo(mSlotIndex)->ItemClass && nullptr != mpTooltipWidget)
	{
		SetToolTip(nullptr);
	}
}
