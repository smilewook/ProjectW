// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
<<<<<<< HEAD
#include "Enemies/WEnemy.h"
#include "Enemies/WEnemyAIController.h"
#include "Player/WCharacter.h"

#include <BehaviorTree/BlackboardComponent.h>
=======
#include "WEnemyAIController.h"
#include "WCharacter.h"
#include "WEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
>>>>>>> 6972ec496f6ca236699b21ab042b35610df03a75


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(ownerComp, nodeMemory);

	auto controllingPawn = Cast<AWEnemy>(ownerComp.GetAIOwner()->GetPawn());
	if (nullptr == controllingPawn)
	{
		return false;
	}

	auto target = Cast<AWCharacter>(ownerComp.GetBlackboardComponent()->GetValueAsObject(AWEnemyAIController::TargetKey));
	if (nullptr == target)
	{
		return false;
	}

	bResult = (target->GetDistanceTo(controllingPawn) <= controllingPawn->GetFinalAttackRange());
	WLOG(Warning, TEXT("Range : %f / %f"), target->GetDistanceTo(controllingPawn), controllingPawn->GetFinalAttackRange());
	return bResult;
}