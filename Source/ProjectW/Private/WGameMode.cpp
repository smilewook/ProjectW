// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameMode.h"
#include "WCharacter.h"
#include "WPlayerController.h"

AWGameMode::AWGameMode()
{
	// 새로 만든 클래스로 교체.
	DefaultPawnClass = AWCharacter::StaticClass();
	PlayerControllerClass = AWPlayerController::StaticClass();
}
