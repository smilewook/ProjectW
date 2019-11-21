// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameMode.h"
#include "WCharacter.h"
#include "WPlayerController.h"

AWGameMode::AWGameMode()
{
	// ���� ���� Ŭ������ ��ü.
	DefaultPawnClass = AWCharacter::StaticClass();
	PlayerControllerClass = AWPlayerController::StaticClass();
}
