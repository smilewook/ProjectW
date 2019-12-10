// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Engine/UserDefinedEnum.h"
#include "ProjectWEnums.generated.h"


#define CONVERT_DISPLAYNAME_TO_STRING(eType, eValue) ( (FindObject<UEnum>(ANY_PACKAGE, eType, true) != nullptr) ? (FindObject<UEnum>(ANY_PACKAGE, eType, true)->GetDisplayNameTextByIndex((int8)eValue)).ToString() : FString("Convert Failed!") );

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT		UMETA(DisplayName = "초기화시작"),
	LOADING		UMETA(DisplayName = "로딩중"),
	READY		UMETA(DisplayName = "준비완료"),
	DEAD		UMETA(DisplayName = "사망")
};

enum class EControlMode
{
	GTA			UMETA(DisplayName = "3인칭"),
	DIABLO		UMETA(DisplayName = "쿼터뷰"),
	NPC			UMETA(DisplayName = "NPC")
};

UENUM(BlueprintType)
enum class EStageState : uint8
{
	READY = 0	UMETA(DisplayName = "전투준비"),
	BATTLE		UMETA(DisplayName = "전투중"),
	COMPLETE	UMETA(DisplayName = "전투끝")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Item_None        UMETA(DisplayName = "없음"),
	Item_Useable	 UMETA(DisplayName = "소모품"),
	Item_Equipment   UMETA(DisplayName = "장비"),
	Item_Material    UMETA(DisplayName = "재료"),
	Item_Misc        UMETA(DisplayName = "잡화"),
	Item_Max
};
