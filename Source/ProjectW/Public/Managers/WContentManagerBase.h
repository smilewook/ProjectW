// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Components/ActorComponent.h"
#include "WContentManagerBase.generated.h"

class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTW_API UWContentManagerBase : public UActorComponent
{
	GENERATED_BODY()
		
	/* Methods */
public:	
	UWContentManagerBase();

	virtual void InitWidget(UUserWidget* pWidget);
	virtual void UpdateWidget();

	virtual void OpenWidget();
	virtual void CloseWidget();

	/* Get/Set */
	FORCEINLINE UUserWidget* const& GetWidget() const { return mpWidget; }
	FORCEINLINE const bool& GetIsOpenWidget() const { return mIsOpenWidget; }

protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	
protected:
	UUserWidget* mpWidget;

	bool mIsOpenWidget;
		
};
