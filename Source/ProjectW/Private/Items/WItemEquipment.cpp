// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemEquipment.h"
#include "Managers/WEquipmentManager.h"
#include "Player/WPlayerCharacter.h"


AWItemEquipment::AWItemEquipment()
{
	mpStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mpStaticMesh->SetupAttachment(RootComponent);
}

bool AWItemEquipment::OnUse(FInventorySlotInfo* const pSlotInfo)
{
	// 플레이어 장비 장착.
	bool bSuccess = false;
	if (nullptr != mpPlayer)
	{
		bSuccess = mpPlayer->GetEquipmentManager()->SetItemEquip(this);

		if (true == bSuccess)
		{
			pSlotInfo->Amount = 0;
			pSlotInfo->pItemClass = nullptr;

			return bSuccess;
		}
		else
		{
			WLOG(Warning, TEXT("AWItemEquipment::OnUse() is failed!!"));
		}
	}
	return bSuccess;
}