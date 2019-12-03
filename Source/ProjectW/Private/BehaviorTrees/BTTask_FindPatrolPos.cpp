// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "WEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"


UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent & ownerComp, uint8 * nodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(ownerComp, nodeMemory);

	auto controllingPawn = ownerComp.GetAIOwner()->GetPawn();
	if (nullptr == controllingPawn)
	{
		return EBTNodeResult::Failed;
	}		

	UNavigationSystemV1* pNavSystem = UNavigationSystemV1::GetNavigationSystem(controllingPawn->GetWorld());
	if (nullptr == pNavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FVector origin = ownerComp.GetBlackboardComponent()->GetValueAsVector(AWEnemyAIController::PatrolPosKey);
	FNavLocation nextPatrol;

	if (pNavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, nextPatrol))
	{
		ownerComp.GetBlackboardComponent()->SetValueAsVector(AWEnemyAIController::PatrolPosKey, nextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
