// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemBase.h"
#include "Player/WPlayerCharacter.h"


AWItemBase::AWItemBase()
{
 	PrimaryActorTick.bCanEverTick = false;

	mpPlayer = nullptr;
}

void AWItemBase::InitOwner(AActor * pOwner)
{
	mpPlayer = Cast<AWPlayerCharacter>(pOwner);
	SetActorHiddenInGame(true);
}

void AWItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

