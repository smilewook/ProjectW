// Fill out your copyright notice in the Description page of Project Settings.


#include "WEquipmentWidget.h"
#include "DragDropOperation/WSlotDragDropOperation.h"
#include "Managers/WContentManagerBase.h"
#include "Managers/WEquipmentManager.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/Equipment/WEquipSlotWidget.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UWEquipmentWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);

	// 장비 슬롯 초기화.
	UWEquipmentManager* pEquipmentManager = Cast<UWEquipmentManager>(mpContentManager);

	mpWeaponSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetWeaponSlot());
	mpWeaponSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpShieldSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetShieldSlot());
	mpShieldSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpHeadSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetHeadSlot());
	mpHeadSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpShoulderSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetShoulderSlot());
	mpShoulderSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpTopSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetTopSlot());
	mpTopSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpBottomSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetBottomSlot());
	mpBottomSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpGloveSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetGloveSlot());
	mpGloveSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpNecklaceSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetNecklaceSlot());
	mpNecklaceSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpEarringSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetEarringSlot());
	mpEarringSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpRingSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetRingSlot());
	mpRingSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
	mpBraceletSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetBraceletSlot());
	mpBraceletSlot->SetTooltipWidget(mpMainWidget->GetTooltipWidget());
}

void UWEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mpCloseButton->OnClicked.AddDynamic(this, &UWEquipmentWidget::OnCloseButtonClicked);
}

bool UWEquipmentWidget::NativeOnDrop(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation)
{
	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		return true;
	}

	return false;
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