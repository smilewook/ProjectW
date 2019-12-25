// Fill out your copyright notice in the Description page of Project Settings.


#include "WEquipmentWidget.h"
#include "DragDropOperation/WSlotDragDropOperation.h"
#include "Managers/WContentManagerBase.h"
#include "Managers/WEquipmentManager.h"
#include "Widgets/Equipment/WEquipSlotWidget.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>


void UWEquipmentWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);

	// 장비 슬롯 초기화.
	UWEquipmentManager* pEquipmentManager = Cast<UWEquipmentManager>(mpContentManager);

	mpWeaponSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetWeaponSlot());
	mpShieldSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetShieldSlot());
	mpHeadSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetHeadSlot());
	mpShoulderSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetShoulderSlot());
	mpTopSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetTopSlot());
	mpBottomSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetBottomSlot());
	mpGloveSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetGloveSlot());
	mpNecklaceSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetNecklaceSlot());
	mpEarringSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetEarringSlot());
	mpRingSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetRingSlot());
	mpBraceletSlot->InitWidget(pEquipmentManager, &pEquipmentManager->GetBraceletSlot());
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