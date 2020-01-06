// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "WGameInstance.generated.h"

/**
 *	ĳ���� ������.
 */
USTRUCT(BlueprintType)
struct FWCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FWCharacterData() : Level(1), MaxHP(100.0f), MaxMP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;

};

/**
 * 
 */
UCLASS()
class PROJECTW_API UWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	/* Method */
public:
	UWGameInstance();

	virtual void Init() override;
	FWCharacterData* GetCharacterData(int32 level);

	FStreamableManager StreamableManager;
	
	/* Properties */
private:
	UPROPERTY()
	class UDataTable* mpCharacterTable;

};
