// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"

#include <Engine/DataTable.h>
#include "ProjectWStructure.generated.h"


class AWItemBase;

class UWInventorySlotWidget;


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
	TSubclassOf<AWItemBase> ItemClass;

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

	FInventorySlotInfo() : SlotIndex(0), pSlotWidget(nullptr), ItemClass(nullptr), Amount(0) {};

	FInventorySlotInfo(int32 slotIndex, UWInventorySlotWidget* pSlot, const TSubclassOf<AWItemBase> itemClass, int32 amount)
		: SlotIndex(slotIndex), pSlotWidget(pSlot), ItemClass(itemClass), Amount(amount) {};

public:
	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	int32 SlotIndex;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	UWInventorySlotWidget* pSlotWidget;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	TSubclassOf<AWItemBase> ItemClass;

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