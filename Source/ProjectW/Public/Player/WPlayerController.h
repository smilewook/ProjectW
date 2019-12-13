// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/PlayerController.h"
#include "WPlayerController.generated.h"


class AWEnemy;
class AWPlayerState;
class UWHUDWidget;
class UWMainWidget;


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

	void NPCKill(AWEnemy* pKilledNPC) const;
	void AddGameScore() const;

	/* Get/Set */
	FORCEINLINE UWMainWidget* const& GetMainWidget() const { return mpMainWidget; }
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/* Properties */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<UWMainWidget> mMainWidgetClass;

private:
	UPROPERTY()
	UWMainWidget* mpMainWidget;

	UPROPERTY()
	AWPlayerState* mpPlayerState;
};
