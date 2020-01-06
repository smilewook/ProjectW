// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameMode.h"
#include "WGameState.h"
#include "Player/WCharacter.h"
#include "Player/WPlayerCharacter.h"
#include "Player/WPlayerController.h"
#include "Player/WPlayerState.h"


AWGameMode::AWGameMode()
{
	//DefaultPawnClass = AWCharacter::StaticClass();
	DefaultPawnClass = AWPlayerCharacter::StaticClass();
	PlayerControllerClass = AWPlayerController::StaticClass();
	PlayerStateClass = AWPlayerState::StaticClass();
	GameStateClass = AWGameState::StaticClass();
}

void AWGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	mpGameState = Cast<AWGameState>(GameState);
}

void AWGameMode::PostLogin(APlayerController* newPlayer)
{
	Super::PostLogin(newPlayer);

	auto playerState = Cast<AWPlayerState>(newPlayer->PlayerState);
	WCHECK(nullptr != playerState);
	playerState->InitPlayerData();
}

void AWGameMode::AddScore(AWPlayerController* pScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto playerController = Cast<AWPlayerController>(It->Get());
		if ((nullptr != playerController) && (pScoredPlayer == playerController))
		{
			playerController->AddGameScore();
			break;
		}
	}

	//mpGameState->AddGameScore();
}
