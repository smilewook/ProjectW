// Fill out your copyright notice in the Description page of Project Settings.


#include "WMainWidget.h"


bool UWMainWidget::InitWidget(AWPlayerCharacter* pPlayer)
{
	if (nullptr != pPlayer)
	{
		mpPlayer = pPlayer;
	}

	return true;
}