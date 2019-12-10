// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WMainWidget.generated.h"


class AWPlayerCharacter;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	bool InitWidget(AWPlayerCharacter* pPlayer);

	/* Properties */
public:

protected:
	AWPlayerCharacter* mpPlayer;

};
