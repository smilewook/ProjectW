// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WMainWidget.generated.h"


class AWPlayerCharacter;

class UWHUDWidget;
class UWInventoryWidget;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	bool InitWidget(AWPlayerCharacter* pPlayer);

	/* Get/Set */
	FORCEINLINE UWHUDWidget* const& GetHUDWidget() const { return mpHUDWidget; }
	FORCEINLINE UWInventoryWidget* const& GetInventoryWidget() const { return mpInventoryWidget; }

protected:
	virtual void NativeConstruct() override;

	/* Properties */
public:

protected:
	AWPlayerCharacter* mpPlayer;

	UPROPERTY()
	UWHUDWidget* mpHUDWidget;

 	UPROPERTY()
 	UWInventoryWidget* mpInventoryWidget;
};
