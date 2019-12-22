// Fill out your copyright notice in the Description page of Project Settings.


#include "WMainWidget.h"
#include "WSlotDragDropOperation.h"
#include "Items/WItemBase.h"
#include "Managers/WEquipmentManager.h"
#include "Managers/WInventoryManager.h"
#include "Managers/WStatManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Equipment/WEquipmentWidget.h"
#include "Widgets/Inventory/WInventoryWidget.h"
#include "Widgets/Inventory/WInventorySlotWidget.h"
#include "widgets/Misc/WItemDestroyWidget.h"
#include "Widgets/Player/WHUDWidget.h"
#include "Widgets/Stat/WStatWidget.h"


void UWMainWidget::NativeConstruct()
{
	
}

bool UWMainWidget::NativeOnDrop(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation)
{
	Super::NativeOnDrop(inGeometry, inDragDropEvent, inOperation);

	// �κ��丮 ������ ���ο� ����Ǿ��� ��� destroy �� �� �ΰ��� ���� ����.
	// �κ��丮 ������ ������ ����ɶ� Ȯ�� ������ �ٸ� �����?.

	if (UWSlotDragDropOperation* pSlotOperation = Cast<UWSlotDragDropOperation>(inOperation))
	{
		UWInventorySlotWidget* pFromSlot = Cast<UWInventorySlotWidget>(pSlotOperation->GetDraggedSlot());
		FInventorySlotInfo* pFromSlotInfo = pFromSlot->GetSlotInfo();
		if (nullptr != pFromSlotInfo->pItemClass)
		{
			mpItemDestroyWidget->Show(pFromSlotInfo);
			return true;
		}		
		return false;
	}
	else
	{
		WLOG(Warning, TEXT("UWMainWidget::NativeOnDrop() ?"));

		return false;
	}	
}

bool UWMainWidget::InitWidget(AWPlayerCharacter* pPlayer)
{
	if (nullptr != pPlayer)
	{
		mpPlayer = pPlayer;
	}
	
	// �� ������ ����/������ �Ŵ��� ���.
	mpHUDWidget->InitWidget(this);
	mpInventoryWidget->InitWidget(this, mpPlayer->GetInventoryManager());
	mpItemDestroyWidget->InitWidget(this, mpPlayer->GetInventoryManager());
	mpStatWidget->InitWidget(this, mpPlayer->GetStatManager());
	mpEquipmentWidget->InitWidget(this, mpPlayer->GetEquipmentManager());

	return true;
}