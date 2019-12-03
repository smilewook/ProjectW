// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/PlayerState.h"
#include "WPlayerState.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);


/**
 * 
 */
UCLASS()
class PROJECTW_API AWPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWPlayerState();

	int32 GetGameScore() const;
	int32 GetGameHighScore() const;
	int32 GetCharacterLevel() const;
	float GetExpRatio() const;
	bool AddExp(int32 inExp);
	void AddGameScore();

	void InitPlayerData();
	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	void SetCharacterLevel(int32 newCharacterLevel);

	/* Properties */
public:
	FString SaveSlotName;

protected:
	UPROPERTY(Transient)
	int32 mGameScore;

	UPROPERTY(Transient)
	int32 mGameHighScore;

	UPROPERTY(Transient)
	int32 mCharacterLevel;

	UPROPERTY(Transient)
	int32 mExp;

private:
	struct FWCharacterData* mCurrentStatData;
};
