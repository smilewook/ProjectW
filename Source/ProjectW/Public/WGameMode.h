// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/GameModeBase.h"
#include "WGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API AWGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* newPlayer) override;
	void AddScore(class AWPlayerController* pPlayerController);

	/* Properties */
private:
	UPROPERTY()
	class AWGameState*  mpGameState;
};
