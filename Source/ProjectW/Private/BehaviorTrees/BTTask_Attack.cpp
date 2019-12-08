// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
<<<<<<< HEAD
#include "Enemies/WEnemyAIController.h"
#include "Enemies/WEnemy.h"
=======
#include "WEnemyAIController.h"
#include "WEnemy.h"
>>>>>>> 6972ec496f6ca236699b21ab042b35610df03a75


UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	mIsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(ownerComp, nodeMemory);

	auto character = Cast<AWEnemy>(ownerComp.GetAIOwner()->GetPawn());
	if (nullptr == character)
	{
		return EBTNodeResult::Failed;
	}
	character->Attack();
	mIsAttacking = true;
	character->OnAttackEnd.AddLambda([this]() -> void {
		mIsAttacking = false;
	});

	return EBTNodeResult::InProgress;	
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, deltaSeconds);

	if (false == mIsAttacking)
	{
		FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	}	
}