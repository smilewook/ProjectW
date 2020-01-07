// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WMainWidget.generated.h"


class AWPlayerCharacter;

class UWEquipmentWidget;
class UWHUDWidget;
class UWInventoryWidget;
class UWItemDestroyWidget;
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

	/* Get/Set */
	FORCEINLINE UWHUDWidget*			const& GetHUDWidget()			const { return mpHUDWidget; }
	FORCEINLINE UWInventoryWidget*		const& GetInventoryWidget()		const { return mpInventoryWidget; }
	FORCEINLINE UWItemDestroyWidget*	const& GetItemDestroyWidget()	const { return mpItemDestroyWidget; }
	FORCEINLINE UWStatWidget*			const& GetStatWidget()			const { return mpStatWidget; }
	FORCEINLINE UWEquipmentWidget*		const& GetEquipmentWidget()		const { return mpEquipmentWidget; }
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

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<UWTooltipWidget> mTooltipWidgetClass;
};
