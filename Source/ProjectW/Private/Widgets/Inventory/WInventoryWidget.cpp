// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryWidget.h"
#include "WInventorySlotWidget.h"
#include "Managers/WContentManagerBase.h"
#include "Managers/WInventoryManager.h"

#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/TextBlock.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>


void UWInventoryWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);

	mpSlotPanel->ClearChildren();
}

bool UWInventoryWidget::CreateSlot(FInventorySlotInfo* pSlotInfo, int32 row, int32 column)
{
	if (nullptr != mSlotWidgetClass)
	{
		if (nullptr == pSlotInfo)
		{
			return false;
		}
		//WLOG(Warning, TEXT("CreateSlot row = %d / column = %d"), row, column);

		UWInventoryManager* pContentManager = Cast<UWInventoryManager>(mpContentManager);
		UWInventorySlotWidget* pInventorySlot = CreateWidget<UWInventorySlotWidget>(GetWorld(), mSlotWidgetClass);
		pInventorySlot->InitWidget(pContentManager, pSlotInfo);
		pInventorySlot->UpdateWidget();

		UUniformGridSlot* pGridSlot = mpSlotPanel->AddChildToUniformGrid(pInventorySlot);
		pGridSlot->SetRow(row);
		pGridSlot->SetColumn(column);

		return true;
	}
	else
	{
		WLOG(Warning, TEXT("UWInventoryWidget::CreateSlots() Failed!"));
		return false;
	}
}

void UWInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mpCloseButton->OnClicked.AddDynamic(this, &UWInventoryWidget::OnCloseButtonClicked);
}

void UWInventoryWidget::OnCloseButtonClicked()
{
	mpContentManager->Close();
}

FReply UWInventoryWidget::NativeOnMouseButtonDown(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent)
{
	if (inMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWContentWidgetBase::NativeOnMouseButtonDown(inGeometry, inMouseEvent);
	}

	return FReply::Unhandled();
}

void UWInventoryWidget::NativeOnDragDetected(const FGeometry & inGeometry, const FPointerEvent & inMouseEvent, UDragDropOperation *& outOperation)
{
	UWContentWidgetBase::NativeOnDragDetected(inGeometry, inMouseEvent, outOperation);
}
