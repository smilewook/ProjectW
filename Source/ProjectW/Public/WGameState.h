// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/GameStateBase.h"
#include "WGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API AWGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWGameState();

	int32 GetTotalGameScore() const;
	void AddGameScore();

	/* Properties */
private:
	UPROPERTY(Transient)
	int32 mTotalGameScore;
};
