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
	// 아이템 아이디.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 ID;

	// 아이템 이름.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FName Name;

	// 아이템 설명.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FText Description;

	// 아이템 아이콘(슬롯에 표시).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	class UTexture2D* pIcon;

	// 사용 가능?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	bool IsUseAble;

	// 사용 텍스트.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FText UseText;

	// 누적 가능?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	bool IsStackAble;

	// 아이템 카테고리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	EItemType ItemType;

	// 아이템 무게.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	float Weight;

	// 레시피.
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
// 	TArray<FInventorySlot> Recipe;

	// 가격.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 Price;

	// 아이템 메쉬.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	class UStaticMesh* pStaticMesh;

	// 메쉬 비율.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FVector MeshScale = FVector(1.f, 1.f, 1.f);

	// 상호작용 반경.
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
	// 아이템 클레스.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventorySlot")
	TSubclassOf<class AWItemBase> ItemClass;

	// 아이템 수량.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventorySlot")
	int Amount;
};