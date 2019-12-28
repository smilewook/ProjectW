// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemEquipment.h"
#include "Managers/WEquipmentManager.h"
#include "Player/WPlayerCharacter.h"

#include <Components/ArrowComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>


AWItemEquipment::AWItemEquipment()
{
	mpArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = mpArrow;

	mpCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	mpCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mpCollision->SetupAttachment(RootComponent);
}

void AWItemEquipment::InitOwner(AActor* pOwner)
{
	AWItemBase::InitOwner(pOwner);
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