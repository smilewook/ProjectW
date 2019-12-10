// Fill out your copyright notice in the Description page of Project Settings.


#include "WContentManagerBase.h"
#include "Widgets/WContentWidgetBase.h"

#include <UserWidget.h>


UWContentManagerBase::UWContentManagerBase()
{
	PrimaryComponentTick.bCanEverTick = false;

	mpWidget = nullptr;
	mIsOpenWidget = false;
}

void UWContentManagerBase::BeginPlay()
{
	Super::BeginPlay();
}

void UWContentManagerBase::InitWidget(UWContentWidgetBase* pWidget)
{
	if (nullptr != pWidget)
	{
		mpWidget = pWidget;
	}
}

void UWContentManagerBase::UpdateWidget()
{
}

void UWContentManagerBase::OpenWidget()
{
	if (false == mIsOpenWidget)
	{
		mIsOpenWidget = true;
		mpWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWContentManagerBase::CloseWidget()
{
	if (true == mIsOpenWidget)
	{
		mIsOpenWidget = false;
		mpWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
