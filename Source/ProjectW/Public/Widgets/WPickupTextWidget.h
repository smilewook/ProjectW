// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WPickupTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTW_API UWPickupTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	FORCEINLINE class UTextBlock* const& GetNameText() const { return mpNameText; }

protected:
	UPROPERTY()
	class UTextBlock* mpNameText;


};
