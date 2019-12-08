// Fill out your copyright notice in the Description page of Project Settings.


#include "WEnemyAIController.h"
<<<<<<< HEAD

#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>
#include <BehaviorTree/BlackboardComponent.h>
=======
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
>>>>>>> 6972ec496f6ca236699b21ab042b35610df03a75


const FName AWEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName AWEnemyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AWEnemyAIController::TargetKey(TEXT("Target"));


AWEnemyAIController::AWEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBOBJECT(TEXT("/Game/AI/BB_Enemy.BB_Enemy"));
	if (BBOBJECT.Succeeded())
	{
		mpBBAsset = BBOBJECT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTOBJECT(TEXT("/Game/AI/BT_Enemy.BT_Enemy"));
	if (BTOBJECT.Succeeded())
	{
		mpBTAsset = BTOBJECT.Object;
	}
}

void AWEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);	
}

void AWEnemyAIController::PlayAI()
{
	if (UseBlackboard(mpBBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(mpBTAsset))
		{
			WLOG(Error, TEXT("AIController couldnt run behavior tree!"));
		}
	}
}

void AWEnemyAIController::StopAI()
{
	auto behaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != behaviorTreeComponent)
	{
		behaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
