// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Engine/UserDefinedEnum.h"
#include "ProjectWEnums.generated.h"


#define CONVERT_DISPLAYNAME_TO_STRING(eType, eValue) ( (FindObject<UEnum>(ANY_PACKAGE, eType, true) != nullptr) ? (FindObject<UEnum>(ANY_PACKAGE, eType, true)->GetDisplayNameTextByIndex((int32)eValue)).ToString() : FString("Convert Failed!") );

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

UENUM(BlueprintType)
enum class EStatAttributeType : uint8
{
	StatAttribute_None		UMETA(DisplayName = "None"),
	StatAttribute_Level		UMETA(DisplayName = "Level"),
	StatAttribute_Exp		UMETA(DisplayName = "EXP"),
	StatAttribute_HP		UMETA(DisplayName = "HP"),
	StatAttribute_MP		UMETA(DisplayName = "MP"),
	StatAttribute_Attack	UMETA(DisplayName = "ATK"),
	StatAttribute_Defense	UMETA(DisplayName = "DEF"),
	StatAttribute_Special	UMETA(DisplayName = "Special"),
	StatAttribute_Critical	UMETA(DisplayName = "Critical"),
	StatAttribute_Dodge		UMETA(DisplayName = "Dodge"),
	StatAttribute_Max
};

UENUM(BlueprintType)
enum class EItemEquipType : uint8
{
	ItemEquip_None		UMETA(DisplayName = "None"),
	ItemEquip_Weapon	UMETA(DisplayName = "Weapon"),
	ItemEquip_Shield	UMETA(DisplayName = "Shield"),
	ItemEquip_Head		UMETA(DisplayName = "Head"),
	ItemEquip_Shoulder	UMETA(DisplayName = "Shoulder"),
	ItemEquip_Top		UMETA(DisplayName = "Top"),
	ItemEquip_Bottom	UMETA(DisplayName = "Bottom"),
	ItemEquip_Glove		UMETA(DisplayName = "Glove"),
	ItemEquip_Necklace	UMETA(DisplayName = "Necklace"),
	ItemEquip_Earring	UMETA(DisplayName = "Earring"),
	ItemEquip_Ring		UMETA(DisplayName = "Ring"),	
	ItemEquip_Bracelet	UMETA(DisplayName = "Bracelet"),
	ItemEquip_Max
};
