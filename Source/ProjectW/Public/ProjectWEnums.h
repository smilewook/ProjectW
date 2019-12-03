// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ProjectWEnums.generated.h"


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};

enum class EControlMode
{
	GTA,
	DIABLO,
	NPC
};

enum class EStageState : uint8
{
	READY = 0,
	BATTLE,
	COMPLETE
};


/**
 * 
 */
UCLASS()
class PROJECTW_API UProjectWEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
