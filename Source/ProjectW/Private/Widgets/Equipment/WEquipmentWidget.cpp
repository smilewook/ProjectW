// Fill out your copyright notice in the Description page of Project Settings.


#include "WEquipmentWidget.h"
#include "Managers/WContentManagerBase.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UWEquipmentWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);

	// 장비 슬롯 초기화.
}

void UWEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mpCloseButton->OnClicked.AddDynamic(this, &UWEquipmentWidget::OnCloseButtonClicked);
}

FReply UWEquipmentWidget::NativeOnMouseButtonDown(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWContentWidgetBase::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
	}

	return FReply::Unhandled();
}

void UWEquipmentWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	UWContentWidgetBase::NativeOnDragDetected(inGeometry, inMouseEvent, outOperation);
}

void UWEquipmentWidget::OnCloseButtonClicked()
{
	mpContentManager->Close();
}

UWEquipSlotWidget* const& UWEquipmentWidget::GetEquipSlotByItemEquipType(EItemEquipType itemEquipType) const
{
	switch (itemEquipType)
	{	
	case EItemEquipType::ItemEquip_Weapon:
		return mpWeaponSlot;
		break;
	case EItemEquipType::ItemEquip_Shield:
		return mpShieldSlot;
		break;
	case EItemEquipType::ItemEquip_Head:
		return mpHeadSlot;
		break;
	case EItemEquipType::ItemEquip_Shoulder:
		return mpShoulderSlot;
		break;
	case EItemEquipType::ItemEquip_Top:
		return mpTopSlot;
		break;
	case EItemEquipType::ItemEquip_Bottom:
		return mpBottomSlot;
		break;
	case EItemEquipType::ItemEquip_Glove:
		return mpGloveSlot;
		break;
	case EItemEquipType::ItemEquip_Necklace:
		return mpNecklaceSlot;
		break;
	case EItemEquipType::ItemEquip_Earring:
		return mpEarringSlot;
		break;
	case EItemEquipType::ItemEquip_Ring:
		return mpRingSlot;
		break;
	case EItemEquipType::ItemEquip_Bracelet:
		return mpBraceletSlot;
		break;
	case EItemEquipType::ItemEquip_None:
	case EItemEquipType::ItemEquip_Max:
	default:
		return mpDummySlot;
		break;
	}
}