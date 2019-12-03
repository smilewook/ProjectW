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

	void PlayAI();
	void StopAI();

private:

	/* Properties */
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
	class UBehaviorTree* mpBTAsset;

	UPROPERTY()
	class UBlackboardData* mpBBAsset;
};
