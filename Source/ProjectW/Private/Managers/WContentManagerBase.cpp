// Fill out your copyright notice in the Description page of Project Settings.


#include "WContentManagerBase.h"
#include "Widgets/WContentWidgetBase.h"

#include <UserWidget.h>


UWContentManagerBase::UWContentManagerBase()
{
	PrimaryComponentTick.bCanEverTick = false;

	mpWidget = nullptr;
	mIsOpen = false;
}

void UWContentManagerBase::BeginPlay()
{
	Super::BeginPlay();
}

void UWContentManagerBase::InitManager(UWContentWidgetBase* pWidget)
{
	if (nullptr != pWidget)
	{
		mpWidget = pWidget;
	}
}

void UWContentManagerBase::UpdateManager()
{
}

void UWContentManagerBase::Open()
{
	if (false == mIsOpen)
	{
		mIsOpen = true;
		mpWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWContentManagerBase::Close()
{
	if (true == mIsOpen)
	{
		mIsOpen = false;
		mpWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
