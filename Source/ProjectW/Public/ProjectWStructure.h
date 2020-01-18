// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"

#include <Engine/DataTable.h>
#include "ProjectWStructure.generated.h"


class AWItemBase;
class AWItemEquipment;

class UWEquipSlotWidget;
class UWInventorySlotWidget;
class UWLootingSlotWidget;


USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_BODY()

public:
	// ������ ���̵�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 ID;

	// ������ �̸�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FName Name;

	// ������ ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FText Description;

	// ������ ������(���Կ� ǥ��).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	class UTexture2D* pIcon;

	// ��� ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	bool IsUseAble;

	// ���� ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	bool IsStackAble;

	// ������ ī�װ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemType ItemType;

	// ������ �Ӽ�.
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
 	TMap<EStatAttributeType, float> ItemStats;

	// ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 Price;

	// ������ �޽�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	class UStaticMesh* pStaticMesh;

	// �޽� ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FVector MeshScale = FVector(1.f, 1.f, 1.f);

	// ��ȣ�ۿ� �ݰ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	float InteractRadius = 100.f;
};

USTRUCT(BlueprintType)
struct FItemContents : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemContent")
	AWItemBase* pItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemContent")
	int32 MinAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemContent")
	int32 MaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemContent")
	int32 Chance;
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo
{
	GENERATED_BODY()

	FInventorySlotInfo() : SlotIndex(0), pSlotWidget(nullptr), pItemClass(nullptr), Amount(0) {};

	FInventorySlotInfo(int32 slotIndex, UWInventorySlotWidget* pSlot, AWItemBase* pItem, int32 amount)
		: SlotIndex(slotIndex), pSlotWidget(pSlot), pItemClass(pItem), Amount(amount) {};

public:
	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	int32 SlotIndex;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	UWInventorySlotWidget* pSlotWidget;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	AWItemBase* pItemClass;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	int32 Amount;
};

USTRUCT(BlueprintType)
struct FStatInfo
{
	GENERATED_BODY();

	FStatInfo() : MaxValue(0.0f), CurrentValue(0.0f) {};

	FStatInfo(EStatAttributeType statType, float maxValue, float currentValue) :
		MaxValue(maxValue), CurrentValue(currentValue) {};

public:
	// ���� �ִ� ��.
	UPROPERTY(EditAnywhere, Category = "StatInfo")
	float MaxValue;

	// ���� ���� ��.
	UPROPERTY(EditAnywhere, Category = "StatInfo")
	float CurrentValue;

	// ������ ���� ����ġ.
	UPROPERTY(EditAnywhere, Category = "StatInfo")
	float IncreaseFromLevelUp;
};

USTRUCT(BlueprintType)
struct FEquipmentSlotInfo
{
	GENERATED_BODY()

	FEquipmentSlotInfo() : pItemClass(nullptr), pSlotWidget(nullptr) {};

public:
	UPROPERTY(VisibleAnywhere, Category = "EquipmentSlotInfo")
	AWItemEquipment* pItemClass;

	UPROPERTY(VisibleAnywhere, Category = "EquipmentSlotInfo")
	UWEquipSlotWidget* pSlotWidget;
};

USTRUCT(BlueprintType)
struct FLootingSlotInfo
{
	GENERATED_BODY()

	FLootingSlotInfo() : ItemClass(nullptr), Amount(0) {};

	FLootingSlotInfo(TSubclassOf<AWItemBase> itemClass, int32 amount) :
		ItemClass(itemClass), Amount(amount) {};

public:
	UPROPERTY(EditAnywhere, Category = "LootingSlotInfo")
	TSubclassOf<AWItemBase> ItemClass;

	UPROPERTY(EditAnywhere, Category = "LootingSlotInfo")
	int32 Amount;
};