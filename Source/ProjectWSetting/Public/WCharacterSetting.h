// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=ProjectW)
class PROJECTWSETTING_API UWCharacterSetting : public UObject
{
	GENERATED_BODY()

	/* Method */
public:
	UWCharacterSetting();
	
	/* Properties */
public:
	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
};
