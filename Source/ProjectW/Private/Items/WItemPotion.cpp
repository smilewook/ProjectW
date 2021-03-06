// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemPotion.h"
#include "Player/WPlayerCharacter.h"
#include "Player/WPlayerController.h"


AWItemPotion::AWItemPotion()
{
	mpStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mpStaticMesh->SetupAttachment(RootComponent);
}

void AWItemPotion::InitOwner(AActor* pOwner)
{
	AWItemBase::InitOwner(pOwner);
}

bool AWItemPotion::OnUse(FInventorySlotInfo* const pSlotInfo)
{
	// 포션 아이템 사용시.
	bool bSuccess = false;
	if (nullptr != mpPlayer)
	{
		FItemInfo itemInfo = GetItemInfo();
		for (auto itemStat : itemInfo.ItemStats)
		{
			if (itemStat.Key == EStatAttributeType::StatAttribute_Exp)
			{
				bSuccess = mpPlayer->AddExp(itemStat.Value);
			}
			else
			{
				bSuccess = mpPlayer->ModifyCurrentStatAttribute(itemStat.Key, itemStat.Value);
			}

			if (true == bSuccess)
			{
				pSlotInfo->Amount--;
				if (pSlotInfo->Amount <= 0)
				{
					pSlotInfo->pItemClass = nullptr;
					Destroy();
				}
				
				return bSuccess;
			}
			else
			{
				WLOG(Warning, TEXT("AWItemPotion::OnUse() is failed!!"));
			}
		}
	}
	return bSuccess;	
}