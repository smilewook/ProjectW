// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerController.h"


void AWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);
}