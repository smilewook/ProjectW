// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WContentWidgetBase.h"
#include "WItemDestroyWidget.generated.h"


struct FInventorySlotInfo;

class UButton;
class UTextBlock;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWItemDestroyWidget : public UWContentWidgetBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	virtual void InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager) override;

	void Show(FInventorySlotInfo* pSlotInfo);
	void Hide();

	/* Get/Set */
	FORCEINLINE UTextBlock* const& GetNameText() const { return mpNameText; }

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;

private:
	UFUNCTION()
	void OnConfrimButtonClicked();
	UFUNCTION()
	void OnCancelButtonClicked();

	/* Properties */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	UTextBlock* mpTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	UTextBlock* mpNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	UTextBlock* mpDescText;

	UPROPERTY()
	UButton* mpConfirmButton;

	UPROPERTY()
	UButton* mpCancelButton;

private:
	FInventorySlotInfo* mpSlotInfo;
};
