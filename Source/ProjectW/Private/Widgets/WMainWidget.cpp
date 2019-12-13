// Fill out your copyright notice in the Description page of Project Settings.


#include "WMainWidget.h"
#include "Managers/WInventoryManager.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Inventory/WInventoryWidget.h"
#include "Widgets/Player/WHUDWidget.h"


void UWMainWidget::NativeConstruct()
{

}

bool UWMainWidget::InitWidget(AWPlayerCharacter* pPlayer)
{
	if (nullptr != pPlayer)
	{
		mpPlayer = pPlayer;
	}
	
	// °¢ À§Á¬¿¡ ¸ÞÀÎ/ÄÁÅÙÃ÷ ¸Å´ÏÀú µî·Ï.
	mpHUDWidget->InitWidget(this);
	mpInventoryWidget->InitWidget(this, mpPlayer->GetInventory());

	WLOG(Warning, TEXT("UWMainWidget::InitWidget()"));
	return true;
}