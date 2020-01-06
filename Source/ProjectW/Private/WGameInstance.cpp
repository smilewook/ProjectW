// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameInstance.h"


UWGameInstance::UWGameInstance()
{
	//FString characterDataPath = TEXT("/Game/GameData/CharacterData.CharacterData");
	FString characterDataPath = TEXT("/Game/GameData/PlayerData.PlayerData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTER(*characterDataPath);
	WCHECK(DT_CHARACTER.Succeeded());
	mpCharacterTable = DT_CHARACTER.Object;
	WCHECK(mpCharacterTable->GetRowMap().Num() > 0);
}

void UWGameInstance::Init()
{
	Super::Init();
}

FWCharacterData* UWGameInstance::GetCharacterData(int32 level)
{
	return mpCharacterTable->FindRow<FWCharacterData>(*FString::FromInt(level), TEXT(""));
}