// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemEquipment.h"


AWItemEquipment::AWItemEquipment()
{
	mpStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	mpStaticMesh->SetupAttachment(RootComponent);
}

bool AWItemEquipment::OnUse(FInventorySlotInfo* const pSlotInfo)
{
	// �÷��̾� ��� ����.
	WLOG(Warning, TEXT("AWItemEquipment::OnUse"));
	return true;
}