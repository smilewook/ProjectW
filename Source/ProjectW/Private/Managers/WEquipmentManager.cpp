// Fill out your copyright notice in the Description page of Project Settings.


#include "WEquipmentManager.h"
#include "Items/WItemEquipment.h"
#include "Managers/WInventoryManager.h"
#include "Managers/WStatManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Equipment/WEquipmentWidget.h"
#include "Widgets/Equipment/WEquipSlotWidget.h"


UWEquipmentManager::UWEquipmentManager()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWEquipmentManager::InitManager(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitManager(pWidget);

	// ��� ���� �ʱ�ȭ.
	InitSlot();
}

void UWEquipmentManager::InitSlot()
{
	// ��� ���� �ʱ�ȭ.
	UWEquipmentWidget* pEquipmentWidget = Cast<UWEquipmentWidget>(mpWidget);
	
	mWeaponSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Weapon);
	mShieldSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Shield);
	mHeadSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Head);
	mShoulderSlot.pSlotWidget	= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Shoulder);
	mTopSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Top);
	mBottomSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Bottom);
	mGloveSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Glove);
	mNecklaceSlot.pSlotWidget	= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Necklace);
	mEarringSlot.pSlotWidget	= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Earring);
	mRingSlot.pSlotWidget		= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Ring);
	mBraceletSlot.pSlotWidget	= pEquipmentWidget->GetEquipSlotByItemEquipType(EItemEquipType::ItemEquip_Bracelet);
}

void UWEquipmentManager::UpdateManager()
{
	// something like that
}

void UWEquipmentManager::Close()
{
	UWContentManagerBase::Close();

	// ��� ���� ���õ� ������&���� ���ͷ���.
	
}

bool UWEquipmentManager::EquipSlot(AWItemEquipment* pItemEquipment)
{
	return SetItemEquip(pItemEquipment);
}

bool UWEquipmentManager::UnequipSlot(AWItemEquipment* pItemEquipment)
{
	EItemEquipType itemEquipType = pItemEquipment->GetItemEquipType();

	switch (itemEquipType)
	{
	case EItemEquipType::ItemEquip_Weapon:
		return UnequipWeaponSlot();
		break;
	case EItemEquipType::ItemEquip_Shield:
		return UnequipShieldSlot();
		break;
	case EItemEquipType::ItemEquip_Head:
		return UnequipHeadSlot();
		break;
	case EItemEquipType::ItemEquip_Shoulder:
		return UnequipShoulderSlot();
		break;
	case EItemEquipType::ItemEquip_Top:
		return UnequipTopSlot();
		break;
	case EItemEquipType::ItemEquip_Bottom:
		return UnequipBottomSlot();
		break;
	case EItemEquipType::ItemEquip_Glove:
		return UnequipGloveSlot();
		break;
	case EItemEquipType::ItemEquip_Necklace:
		return UnequipNecklaceSlot();
		break;
	case EItemEquipType::ItemEquip_Earring:
		return UnequipEarringSlot();
		break;
	case EItemEquipType::ItemEquip_Ring:
		return UnequipRingSlot();
		break;
	case EItemEquipType::ItemEquip_Bracelet:
		return UnequipBraceletSlot();
		break;
	case EItemEquipType::ItemEquip_None:
	case EItemEquipType::ItemEquip_Max:
	default:
		break;
	}

	return false;
}

bool UWEquipmentManager::SetItemEquip(AWItemEquipment* pItemEquipment)
{
	EItemEquipType itemEquipType = pItemEquipment->GetItemEquipType();

	switch (itemEquipType)
	{
	case EItemEquipType::ItemEquip_Weapon:
		return EquipWeaponSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Shield:
		return EquipShieldSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Head:
		return EquipHeadSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Shoulder:
		return EquipShoulderSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Top:
		return EquipTopSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Bottom:
		return EquipBottomSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Glove:
		return EquipGloveSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Necklace:
		return EquipNecklaceSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Earring:
		return EquipEarringSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Ring:
		return EquipRingSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_Bracelet:
		return EquipBraceletSlot(pItemEquipment);
		break;
	case EItemEquipType::ItemEquip_None:
	case EItemEquipType::ItemEquip_Max:
	default:
		break;
	}

	return false;
}

bool UWEquipmentManager::EquipWeaponSlot(AWItemEquipment* pItemEquipment)
{
	UnequipWeaponSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipWeaponSlot()"));
	return false;
}

bool UWEquipmentManager::EquipShieldSlot(AWItemEquipment* pItemEquipment)
{
	UnequipShieldSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipShieldSlot()"));
	return false;
}

bool UWEquipmentManager::EquipHeadSlot(AWItemEquipment* pItemEquipment)
{
	UnequipHeadSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipHeadSlot()"));
	return false;
}

bool UWEquipmentManager::EquipShoulderSlot(AWItemEquipment * pItemEquipment)
{
	UnequipShoulderSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipShoulderSlot()"));
	return false;
}

bool UWEquipmentManager::EquipTopSlot(AWItemEquipment* pItemEquipment)
{
	UnequipTopSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipTopSlot()"));
	return false;
}

bool UWEquipmentManager::EquipBottomSlot(AWItemEquipment* pItemEquipment)
{
	UnequipBottomSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipBottomSlot()"));
	return false;
}

bool UWEquipmentManager::EquipGloveSlot(AWItemEquipment* pItemEquipment)
{
	UnequipGloveSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipGloveSlot()"));
	return false;
}

bool UWEquipmentManager::EquipNecklaceSlot(AWItemEquipment* pItemEquipment)
{
	UnequipNecklaceSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipNecklaceSlot()"));
	return false;
}

bool UWEquipmentManager::EquipEarringSlot(AWItemEquipment* pItemEquipment)
{
	UnequipEarringSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipEarringSlot()"));
	return false;
}

bool UWEquipmentManager::EquipRingSlot(AWItemEquipment* pItemEquipment)
{
	UnequipRingSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipRingSlot()"));
	return false;
}

bool UWEquipmentManager::EquipBraceletSlot(AWItemEquipment* pItemEquipment)
{
	UnequipBraceletSlot();
	WLOG(Warning, TEXT("UWEquipmentManager::EquipBraceletSlot()"));
	return false;
}

bool UWEquipmentManager::UnequipWeaponSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mWeaponSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mWeaponSlot.pItemClass);
			if (true == bSuccess)
			{
				//_UpdatePlayerStats(m_WeaponSlot.pItem, false);
				//FDetachmentTransformRules Param(EDetachmentRule::KeepWorld, false);
				//m_WeaponSlot.pItem->DetachFromActor(Param);
				//m_WeaponSlot.pItem->SetActorHiddenInGame(true);
				mWeaponSlot.pItemClass = nullptr;
				mWeaponSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipShieldSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipHeadSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipShoulderSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipTopSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipBottomSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipGloveSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipNecklaceSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipEarringSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipRingSlot()
{
	return false;
}

bool UWEquipmentManager::UnequipBraceletSlot()
{
	return false;
}