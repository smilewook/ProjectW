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
	
	bool AddExp(int32 inExp);
	void AddGameScore();

	void InitPlayerData();
	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

	/* Get/Set */
	FORCEINLINE const int32 GetGameScore()		const { return mGameScore; }
	FORCEINLINE const int32 GetGameHighScore()	const { return mGameHighScore; }
	FORCEINLINE const int32 GetCharacterLevel() const { return mCharacterLevel; }
	FORCEINLINE const int32 GetExp()			const { return mCurrentExp; }
	int32 GetExpRatio() const;

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
	int32 mCurrentExp;

	UPROPERTY(Transient)
	int32 mMaxExp;

private:
	struct FWCharacterData* mCurrentStatData;

};
