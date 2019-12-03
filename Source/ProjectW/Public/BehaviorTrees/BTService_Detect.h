// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
	
	/* Method */
public:
	UBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds) override;

	/* Properties */
};
