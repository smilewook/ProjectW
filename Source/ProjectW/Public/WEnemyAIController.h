// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "AIController.h"
#include "WEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API AWEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWEnemyAIController();

	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnUnPossess() override;

private:
	void OnRepeatTimer();

	/* Properties */
private:
	FTimerHandle mRepeatTimerHandle;
	float mRepeatInterval;
};
