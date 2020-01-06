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

	// 장비 슬롯 초기화.
	InitSlot();
}

void UWEquipmentManager::InitSlot()
{
	// 장비 슬롯 초기화.
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
	// 기본 스탯 설정 이후의 장비 스탯들 설정할때 필요.
}

void UWEquipmentManager::Close()
{
	UWContentManagerBase::Close();

	// 장비 장착 관련된 컨텐츠&위젯 인터렉션.
	
}

/* 아이템 장비 장착 */
bool UWEquipmentManager::EquipSlot(AWItemEquipment* pItemEquipment)
{
	return SetItemEquip(pItemEquipment);
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
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipWeaponSlot()"));
	UnequipWeaponSlot();

	mWeaponSlot.pItemClass = pItemEquipment;
	mWeaponSlot.pSlotWidget->Show();

	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	pPlayer->SetWeapon(pItemEquipment);

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipShieldSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipShieldSlot()"));
	UnequipShieldSlot();

	mShieldSlot.pItemClass = pItemEquipment;
	mShieldSlot.pSlotWidget->Show();

	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	pPlayer->SetSecondWeapon(pItemEquipment);

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipHeadSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipHeadSlot()"));
	UnequipHeadSlot();
	
	mHeadSlot.pItemClass = pItemEquipment;
	mHeadSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipShoulderSlot(AWItemEquipment * pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipShoulderSlot()"));
	UnequipShoulderSlot();
	
	mShoulderSlot.pItemClass = pItemEquipment;
	mShoulderSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipTopSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipTopSlot()"));
	UnequipTopSlot();
	
	mTopSlot.pItemClass = pItemEquipment;
	mTopSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipBottomSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipBottomSlot()"));
	UnequipBottomSlot();
	
	mBottomSlot.pItemClass = pItemEquipment;
	mBottomSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipGloveSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipGloveSlot()"));
	UnequipGloveSlot();
	
	mGloveSlot.pItemClass = pItemEquipment;
	mGloveSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipNecklaceSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipNecklaceSlot()"));
	UnequipNecklaceSlot();
	
	mNecklaceSlot.pItemClass = pItemEquipment;
	mNecklaceSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipEarringSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipEarringSlot()"));
	UnequipEarringSlot();
	
	mEarringSlot.pItemClass = pItemEquipment;
	mEarringSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipRingSlot(AWItemEquipment* pItemEquipment)
{
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipRingSlot()"));
	UnequipRingSlot();
	
	mRingSlot.pItemClass = pItemEquipment;
	mRingSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

bool UWEquipmentManager::EquipBraceletSlot(AWItemEquipment* pItemEquipment)
{
	UnequipBraceletSlot();
	//WLOG(Warning, TEXT("UWEquipmentManager::EquipBraceletSlot()"));
	
	mBraceletSlot.pItemClass = pItemEquipment;
	mBraceletSlot.pSlotWidget->Show();

	UpdatePlayerStats(pItemEquipment, true);

	return true;
}

/* 아이템 장비 탈착 */
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
				pPlayer->SetWeapon(nullptr);
				UpdatePlayerStats(mWeaponSlot.pItemClass, false);				

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
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mShieldSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mShieldSlot.pItemClass);
			if (true == bSuccess)
			{
				pPlayer->SetSecondWeapon(nullptr);
				UpdatePlayerStats(mShieldSlot.pItemClass, false);

				mShieldSlot.pItemClass = nullptr;
				mShieldSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipHeadSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mHeadSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mHeadSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mHeadSlot.pItemClass, false);

				mHeadSlot.pItemClass = nullptr;
				mHeadSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipShoulderSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mShoulderSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mShoulderSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mShoulderSlot.pItemClass, false);

				mShoulderSlot.pItemClass = nullptr;
				mShoulderSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipTopSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mTopSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mTopSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mTopSlot.pItemClass, false);

				mTopSlot.pItemClass = nullptr;
				mTopSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipBottomSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mBottomSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mBottomSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mBottomSlot.pItemClass, false);

				mBottomSlot.pItemClass = nullptr;
				mBottomSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipGloveSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mGloveSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mGloveSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mGloveSlot.pItemClass, false);

				mGloveSlot.pItemClass = nullptr;
				mGloveSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipNecklaceSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mNecklaceSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mNecklaceSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mNecklaceSlot.pItemClass, false);

				mNecklaceSlot.pItemClass = nullptr;
				mNecklaceSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipEarringSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mEarringSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mEarringSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mEarringSlot.pItemClass, false);

				mEarringSlot.pItemClass = nullptr;
				mEarringSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipRingSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mRingSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mRingSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mRingSlot.pItemClass, false);

				mRingSlot.pItemClass = nullptr;
				mRingSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

bool UWEquipmentManager::UnequipBraceletSlot()
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	if (::IsValid(pPlayer))
	{
		if (nullptr != mBraceletSlot.pItemClass)
		{
			bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mBraceletSlot.pItemClass);
			if (true == bSuccess)
			{
				UpdatePlayerStats(mBraceletSlot.pItemClass, false);

				mBraceletSlot.pItemClass = nullptr;
				mBraceletSlot.pSlotWidget->Hide();
				return true;
			}
		}
	}
	return false;
}

void UWEquipmentManager::UpdatePlayerStats(AWItemEquipment* pItemEquipment, bool isAdd)
{
	// 무기 장착에 따른 스탯 변경 필요.
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	FItemInfo itemInfo = pItemEquipment->GetItemInfo();

	int32 valueRate = isAdd ? 1 : -1;

	for (auto itemStat : itemInfo.ItemStats)
	{
		// 장비 장착시 max만 채울것인가? current도 채울것인가?
		pPlayer->ModifyMaxStatAttribute(itemStat.Key, itemStat.Value * valueRate);
		//pPlayer->ModifyCurrentStatAttribute(itemStat.Key, itemStat.Value * valueRate);
	}
}