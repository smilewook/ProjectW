// Fill out your copyright notice in the Description page of Project Settings.


#include "WEnemyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


AWEnemyAIController::AWEnemyAIController()
{
	mRepeatInterval = 3.0f;
}

void AWEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);
	
	GetWorld()->GetTimerManager().SetTimer(mRepeatTimerHandle, this, &AWEnemyAIController::OnRepeatTimer, mRepeatInterval, true);
}

void AWEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(mRepeatTimerHandle);
}

void AWEnemyAIController::OnRepeatTimer()
{
	auto currentPawn = GetPawn();
	WCHECK(nullptr != currentPawn);

	UNavigationSystemV1* pNavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == pNavSystem) return;
	
	FNavLocation nextLocation;
	if (pNavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, nextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, nextLocation.Location);
		WLOG(Warning, TEXT("next location : %s"), *nextLocation.Location.ToString());
	}
}
