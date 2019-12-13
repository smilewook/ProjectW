// Fill out your copyright notice in the Description page of Project Settings.


#include "WInventoryWidget.h"
#include "WInventorySlotWidget.h"

#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/TextBlock.h>
#include <Components/UniformGridPanel.h>
#include <Components/UniformGridSlot.h>


bool UWInventoryWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	UWContentWidgetBase::InitWidget(pMainWidget, pContentManager);
}

bool UWInventoryWidget::CreateSlot(FInventorySlotInfo* pSlotInfo, int row, int column)
{
	if (nullptr != mSlotWidgetClass)
	{
		if (nullptr == pSlotInfo)
		{
			return false;
		}
		WLOG(Warning, TEXT("CreateSlot row = %d / column = %d"), row, column);

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
	mpContentManager->CloseWidget();
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
