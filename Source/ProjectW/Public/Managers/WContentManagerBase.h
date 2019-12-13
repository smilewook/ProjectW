// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Components/ActorComponent.h"
#include "WContentManagerBase.generated.h"


class UWContentWidgetBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTW_API UWContentManagerBase : public UActorComponent
{
	GENERATED_BODY()
		
	/* Methods */
public:	
	UWContentManagerBase();

	virtual void InitWidget(UWContentWidgetBase* pWidget);
	virtual void UpdateWidget();

	virtual void Open();
	virtual void Close();

	/* Get/Set */
	FORCEINLINE UWContentWidgetBase* const& GetWidget() const { return mpWidget; }
	FORCEINLINE const bool& GetIsOpen() const { return mIsOpen; }

protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	
protected:
	UWContentWidgetBase* mpWidget;

	bool mIsOpen;
		
};
