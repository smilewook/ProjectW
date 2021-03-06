// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWStructure.h"
#include "Blueprint/UserWidget.h"
#include "WMainWidget.generated.h"


class AWItemBase;
class AWPlayerCharacter;

class UWAcquireItemWidget;
class UWEquipmentWidget;
class UWHUDWidget;
class UWInventoryWidget;
class UWItemDestroyWidget;
class UWLootingWidget;
class UWStatWidget;
class UWTooltipWidget;


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

	void AddAcquireItemQueue(AWItemBase* newItemClass, int32 amount);
	void EndAcquireItemMessage();

	/* Get/Set */
	FORCEINLINE UWEquipmentWidget*		const& GetEquipmentWidget()		const { return mpEquipmentWidget; }
	FORCEINLINE UWHUDWidget*			const& GetHUDWidget()			const { return mpHUDWidget; }
	FORCEINLINE UWInventoryWidget*		const& GetInventoryWidget()		const { return mpInventoryWidget; }
	FORCEINLINE UWItemDestroyWidget*	const& GetItemDestroyWidget()	const { return mpItemDestroyWidget; }
	FORCEINLINE UWLootingWidget*		const& GetLootingWidget()		const { return mpLootingWidget; }
	FORCEINLINE UWStatWidget*			const& GetStatWidget()			const { return mpStatWidget; }
	FORCEINLINE UWTooltipWidget*		const& GetTooltipWidget()		const { return mpToolipWidget; }

protected:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& inGeometry, const FDragDropEvent& inDragDropEvent, UDragDropOperation* inOperation) override;

	/* Properties */
public:

protected:
	AWPlayerCharacter* mpPlayer;

	UPROPERTY()
	UWHUDWidget* mpHUDWidget;

 	UPROPERTY()
 	UWInventoryWidget* mpInventoryWidget;

	UPROPERTY()
	UWItemDestroyWidget* mpItemDestroyWidget;

	UPROPERTY()
	UWStatWidget* mpStatWidget;

	UPROPERTY()
	UWEquipmentWidget* mpEquipmentWidget;

	UPROPERTY()
	UWTooltipWidget* mpToolipWidget;

	UPROPERTY()
	UWAcquireItemWidget* mpAcquireItemWidget;

	UPROPERTY()
	UWLootingWidget* mpLootingWidget;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWTooltipWidget> mTooltipWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWAcquireItemWidget> mAcquireWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	float mAcquireDuration;

private:
	TArray<FInventorySlotInfo> mAcquireItemsQueue;

	
};
