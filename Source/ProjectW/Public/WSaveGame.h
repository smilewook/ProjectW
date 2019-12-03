// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/SaveGame.h"
#include "WSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API UWSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	/* Method */
public:
	UWSaveGame();

	/* Properties */
public:
	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;
	

protected:
	
};
