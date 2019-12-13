// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WContentWidgetBase.h"
#include "WInventoryWidget.generated.h"


class UWMainWidget;
class UWInventorySlotWidget;

class UButton;
class UScrollBox;
class UTextBlock;
class UUniformGridPanel;

struct FInventorySlotInfo;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWInventoryWidget : public UWContentWidgetBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	virtual void InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager) override;

	bool CreateSlot(FInventorySlotInfo* pSlotInfo, int32 row, int32 column);

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;

private:
	UFUNCTION()
	void OnCloseButtonClicked();

	/* Properties */
public:

protected:
	UPROPERTY()
	UTextBlock* mpNameText;

	UPROPERTY()
	UButton* mpCloseButton;

	UPROPERTY()
	UScrollBox* mpScrollBox;

	UPROPERTY()
	UUniformGridPanel* mpSlotPanel;

	UPROPERTY()
	UTextBlock* mpAmountText;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWInventorySlotWidget> mSlotWidgetClass;

private:

};
