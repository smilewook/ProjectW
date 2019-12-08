// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TurnToTarget.h"
#include "Enemies/WEnemyAIController.h"
#include "Enemies/WEnemy.h"
#include "Player/WCharacter.h"

#include <BehaviorTree/BlackboardComponent.h>


UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(ownerComp, nodeMemory);

	auto character = Cast<AWEnemy>(ownerComp.GetAIOwner()->GetPawn());
	if (nullptr == character)
	{
		return EBTNodeResult::Failed;
	}
	
	auto target = Cast<AWCharacter>(ownerComp.GetBlackboardComponent()->GetValueAsObject(AWEnemyAIController::TargetKey));
	if (nullptr == target)
	{
		return EBTNodeResult::Failed;
	}

	FVector lookVector = target->GetActorLocation() - character->GetActorLocation();
	lookVector.Z = 0.0f;
	FRotator targetRotation = FRotationMatrix::MakeFromX(lookVector).Rotator();
	character->SetActorRotation(FMath::RInterpTo(character->GetActorRotation(), targetRotation, GetWorld()->GetDeltaSeconds(), 1.0f));

	return EBTNodeResult::InProgress;
}
