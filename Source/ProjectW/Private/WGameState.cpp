// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameState.h"


AWGameState::AWGameState()
{
	mTotalGameScore = 0;
}

int32 AWGameState::GetTotalGameScore() const
{
	return mTotalGameScore;
}

void AWGameState::AddGameScore()
{
	mTotalGameScore++;
}