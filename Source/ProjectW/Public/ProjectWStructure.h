// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"

#include <Engine/DataTable.h>
#include "ProjectWStructure.generated.h"


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

	// ��� ����?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	bool IsUseAble;

	// ��� �ؽ�Ʈ.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FText UseText;

	// ���� ����?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	bool IsStackAble;

	// ������ ī�װ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemType ItemType;

	// ������ ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	float Weight;

	// ������.
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
// 	TArray<FInventorySlot> Recipe;

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
	TSubclassOf<class AWItemBase> ItemClass;

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

	FInventorySlotInfo(int32 slotIndex, class UWInventorySlotWidget* pSlot, AWItemBase* pItem, int32 amount)
		: SlotIndex(slotIndex), pSlotWidget(pSlot), pItemClass(pItem), Amount(amount) {};

public:
	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	int32 SlotIndex;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	class UWInventorySlotWidget* pSlotWidget;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	AWItemBase * pItemClass;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlotInfo")
	int32 Amount;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

public:
	FInventorySlot() {};
	FInventorySlot(const TSubclassOf<class AWItemBase> itemClass, const int& amount)
		:ItemClass(itemClass), Amount(amount) {};

public:
	// ������ Ŭ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventorySlot")
	TSubclassOf<class AWItemBase> ItemClass;

	// ������ ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventorySlot")
	int Amount;
};