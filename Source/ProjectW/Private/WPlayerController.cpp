// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerController.h"
#include "WCharacter.h"
#include "WEnemy.h"
#include "WHUDWidget.h"
#include "WPlayerState.h"


AWPlayerController::AWPlayerController()
{
	static ConstructorHelpers::FClassFinder<UWHUDWidget> UI_HUD_C(TEXT("/Game/Widgets/WB_HUD.WB_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		mHUDWidgetClass = UI_HUD_C.Class;
	}
}

void AWPlayerController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);
}

UWHUDWidget* AWPlayerController::GetHUDWidget() const
{
	return mpHUDWidget;
}

void AWPlayerController::NPCKill(AWEnemy * pKilledNPC) const
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

	mpHUDWidget = CreateWidget<UWHUDWidget>(this, mHUDWidgetClass);
	mpHUDWidget->AddToViewport();

	mpPlayerState = Cast<AWPlayerState>(PlayerState);
	WCHECK(nullptr != mpPlayerState);
	mpHUDWidget->BindPlayerState(mpPlayerState);
	mpPlayerState->OnPlayerStateChanged.Broadcast();
}

void AWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
