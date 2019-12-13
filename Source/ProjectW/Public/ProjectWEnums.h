// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Engine/UserDefinedEnum.h"
#include "ProjectWEnums.generated.h"


#define CONVERT_DISPLAYNAME_TO_STRING(eType, eValue) ( (FindObject<UEnum>(ANY_PACKAGE, eType, true) != nullptr) ? (FindObject<UEnum>(ANY_PACKAGE, eType, true)->GetDisplayNameTextByIndex((int8)eValue)).ToString() : FString("Convert Failed!") );

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT		UMETA(DisplayName = "�ʱ�ȭ����"),
	LOADING		UMETA(DisplayName = "�ε���"),
	READY		UMETA(DisplayName = "�غ�Ϸ�"),
	DEAD		UMETA(DisplayName = "���")
};

enum class EControlMode
{
	GTA			UMETA(DisplayName = "3��Ī"),
	DIABLO		UMETA(DisplayName = "���ͺ�"),
	NPC			UMETA(DisplayName = "NPC")
};

UENUM(BlueprintType)
enum class EStageState : uint8
{
	READY = 0	UMETA(DisplayName = "�����غ�"),
	BATTLE		UMETA(DisplayName = "������"),
	COMPLETE	UMETA(DisplayName = "������")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Item_None        UMETA(DisplayName = "None"),
	Item_Useable	 UMETA(DisplayName = "Useable"),
	Item_Equipment   UMETA(DisplayName = "Equipment"),
	Item_Material    UMETA(DisplayName = "Material"),
	Item_Misc        UMETA(DisplayName = "Misc"),
	Item_Max
};
