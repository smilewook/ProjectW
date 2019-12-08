// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
<<<<<<< HEAD
#include "Enemies/WEnemyAIController.h"
#include "Player/WCharacter.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <DrawDebugHelpers.h>
=======
#include "WEnemyAIController.h"
#include "WCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
>>>>>>> 6972ec496f6ca236699b21ab042b35610df03a75


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickNode(ownerComp, nodeMemory, deltaSeconds);

	APawn* pControllingPawn = ownerComp.GetAIOwner()->GetPawn();
	if (nullptr == pControllingPawn)
	{
		return;
	}

	UWorld* pWorld = pControllingPawn->GetWorld();
	FVector center = pControllingPawn->GetActorLocation();
	float detectRadius = 600.0f;

	if (nullptr == pWorld)
	{
		return;
	}

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams collisionQueryParam(NAME_None, false, pControllingPawn);
	bool bResult = pWorld->OverlapMultiByChannel(
		overlapResults,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(detectRadius),
		collisionQueryParam
	);

	if (true == bResult)
	{
		for (auto overlapResult : overlapResults)
		{
			AWCharacter* pCharacter = Cast<AWCharacter>(overlapResult.GetActor());
			if (nullptr != pCharacter && pCharacter->GetController()->IsPlayerController())
			{
				ownerComp.GetBlackboardComponent()->SetValueAsObject(AWEnemyAIController::TargetKey, pCharacter);

				DrawDebugSphere(pWorld, center, detectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(pWorld, pCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(pWorld, pControllingPawn->GetActorLocation(), pCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
	else
	{
		ownerComp.GetBlackboardComponent()->SetValueAsObject(AWEnemyAIController::TargetKey, nullptr);
	}

	// 디버깅 그리기
	DrawDebugSphere(pWorld, center, detectRadius, 16, FColor::Red, false, 0.2f);
}