// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerState.h"
#include "WGameInstance.h"
#include "WSaveGame.h"


AWPlayerState::AWPlayerState()
{
	mCharacterLevel = 1;
	mGameScore = 0;
	mGameHighScore = 0;
	mExp = 0;
	SaveSlotName = TEXT("Player1");
}

int32 AWPlayerState::GetGameScore() const
{
	return mGameScore;
}

int32 AWPlayerState::GetGameHighScore() const
{
	return mGameHighScore;
}

int32 AWPlayerState::GetCharacterLevel() const
{
	return mCharacterLevel;
}

void AWPlayerState::InitPlayerData()
{
	auto saveGame = Cast<UWSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == saveGame)
	{
		saveGame = GetMutableDefault<UWSaveGame>();
	}

	SetPlayerName(saveGame->PlayerName);
 	SetCharacterLevel(saveGame->Level);
 	mGameScore = 0;
 	mGameHighScore = saveGame->HighScore;
 	mExp = saveGame->Exp;
 	SavePlayerData();
}

void AWPlayerState::SavePlayerData()
{
	UWSaveGame* pNewSaveData = NewObject<UWSaveGame>();
	pNewSaveData->PlayerName = GetPlayerName();
	pNewSaveData->Level = mCharacterLevel;
	pNewSaveData->Exp = mExp;
	pNewSaveData->HighScore = mGameHighScore;

	if (!UGameplayStatics::SaveGameToSlot(pNewSaveData, SaveSlotName, 0))
	{
		WLOG(Error, TEXT("SaveGame Error!"));
	}
}

float AWPlayerState::GetExpRatio() const
{
	if (mCurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)mExp / (float)mCurrentStatData->NextExp;
	WLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, mExp, mCurrentStatData->NextExp);
	return Result;
}

bool AWPlayerState::AddExp(int32 inExp)
{
	if (mCurrentStatData->NextExp == -1)
		return false;

	bool didLevelUp = false;
	mExp = mExp + inExp;
	if (mExp >= mCurrentStatData->NextExp)
	{
		mExp -= mCurrentStatData->NextExp;
		SetCharacterLevel(mCharacterLevel + 1);
		didLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
	
	return didLevelUp;
}

void AWPlayerState::AddGameScore()
{
	mGameScore++;
	if (mGameScore >= mGameHighScore)
	{
		mGameHighScore = mGameScore;
	}

	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void AWPlayerState::SetCharacterLevel(int32 newCharacterLevel)
{
	auto gameInstance = Cast<UWGameInstance>(GetGameInstance());
	WCHECK(nullptr != gameInstance);

	mCurrentStatData = gameInstance->GetCharacterData(newCharacterLevel);
	WCHECK(nullptr != mCurrentStatData);

	mCharacterLevel = newCharacterLevel;
}