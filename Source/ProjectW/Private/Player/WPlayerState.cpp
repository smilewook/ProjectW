// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerState.h"
#include "WGameInstance.h"
#include "WSaveGame.h"


AWPlayerState::AWPlayerState()
{
	mCharacterLevel = 1;
	mGameScore = 0;
	mGameHighScore = 0;
	mCurrentExp = 0;
	SaveSlotName = TEXT("Player1");
}

void AWPlayerState::InitPlayerData()
{
	// 로딩 작업 이전까진 리셋.
	SetPlayerName(TEXT("SmileWook"));
	SetCharacterLevel(mCharacterLevel);

	OnPlayerStateChanged.Broadcast();
	return;

	auto saveGame = Cast<UWSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == saveGame)
	{
		saveGame = GetMutableDefault<UWSaveGame>();
	}

	SetPlayerName(saveGame->PlayerName);
 	SetCharacterLevel(saveGame->Level);
 	mGameScore = 0;
 	mGameHighScore = saveGame->HighScore;
	mCurrentExp = saveGame->Exp;

	OnPlayerStateChanged.Broadcast();
 	SavePlayerData();
}

void AWPlayerState::SavePlayerData()
{
	UWSaveGame* pNewSaveData = NewObject<UWSaveGame>();
	pNewSaveData->PlayerName = GetPlayerName();
	pNewSaveData->Level = mCharacterLevel;
	pNewSaveData->Exp = mCurrentExp;
	pNewSaveData->HighScore = mGameHighScore;

	if (!UGameplayStatics::SaveGameToSlot(pNewSaveData, SaveSlotName, 0))
	{
		WLOG(Error, TEXT("SaveGame Error!"));
	}
}

int32 AWPlayerState::GetExpRatio() const
{
	if (nullptr == mCurrentStatData || mCurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0;

	int32 result = (float)mCurrentExp / (float)mMaxExp * 100;
	WLOG(Warning, TEXT("AWPlayerState::GetExpRatio() : %d, Current : %d, Next : %d"), result, mCurrentExp, mMaxExp);
	return result;
}

bool AWPlayerState::AddExp(int32 inExp)
{
	if (mCurrentStatData->NextExp == -1)
		return false;

	bool didLevelUp = false;
	mCurrentExp = mCurrentExp + inExp;
	if (mCurrentExp >= mMaxExp)
	{
		mCurrentExp -= mMaxExp;
		SetCharacterLevel(mCharacterLevel + 1);
		didLevelUp = true;
	}
	WLOG(Warning, TEXT("AWPlayerState::AddExp() : %d, Current : %d, Next : %d"), GetExpRatio(), mCurrentExp, mMaxExp);

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
	mMaxExp += mCurrentStatData->NextExp;

	mCharacterLevel = newCharacterLevel;
}