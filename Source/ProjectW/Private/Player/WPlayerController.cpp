// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerController.h"
#include "WCharacter.h"
#include "WPlayerCharacter.h"
#include "WPlayerState.h"
#include "Enemies/WEnemy.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/Player/WHUDWidget.h"



AWPlayerController::AWPlayerController()
{
	static ConstructorHelpers::FClassFinder<UWMainWidget> MAIN_WIDGET_C(TEXT("/Game/Widgets/WB_Main.WB_Main_C"));
	if (MAIN_WIDGET_C.Succeeded())
	{
		mMainWidgetClass = MAIN_WIDGET_C.Class;
	}
}

void AWPlayerController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);
}

void AWPlayerController::NPCKill(AWEnemy* pKilledNPC) const
{
	mpPlayerState->AddExp(pKilledNPC->GetExp());
}

void AWPlayerController::AddGameScore() const
{
	mpPlayerState->AddGameScore();
}

void AWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);

	mpPlayerState = Cast<AWPlayerState>(PlayerState);
	WCHECK(nullptr != mpPlayerState);

	mpMainWidget = CreateWidget<UWMainWidget>(this, mMainWidgetClass);
	mpMainWidget->AddToViewport();	

	mpMainWidget->GetHUDWidget()->BindPlayerState(mpPlayerState);
	mpPlayerState->OnPlayerStateChanged.Broadcast();
}

void AWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
