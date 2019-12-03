// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemBase.h"


AWItemBase::AWItemBase()
{
 	PrimaryActorTick.bCanEverTick = false;

	mName = *GetName();
}

void AWItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

