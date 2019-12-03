// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/PlayerController.h"
#include "WPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API AWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWPlayerController();

	virtual void OnPossess(APawn* aPawn) override;

	class UWHUDWidget* GetHUDWidget() const;
	void NPCKill(class AWEnemy* pKilledNPC) const;
	void AddGameScore() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/* Properties */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UWHUDWidget> mHUDWidgetClass;

private:
	UPROPERTY()
	class UWHUDWidget* mpHUDWidget;

	UPROPERTY()
	class AWPlayerState* mpPlayerState;
};
