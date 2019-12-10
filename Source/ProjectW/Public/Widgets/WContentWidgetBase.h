// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Blueprint/UserWidget.h"
#include "WContentWidgetBase.generated.h"


class UWMainWidget;
class UWContentManagerBase;


/**
 * 
 */
UCLASS()
class PROJECTW_API UWContentWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
	/* Methods */
public:
	virtual bool InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager);
	virtual void UpdateWidget();

	/* Get/Set */
	FORCEINLINE UWMainWidget* const& GetMainWidget() const { return mpMainWidget; }
	FORCEINLINE UWContentManagerBase* const& GetContentManager()  const { return mpContentManager; }
	
	FORCEINLINE void SetMainWidget(UWMainWidget* pMainWidget) { mpMainWidget = pMainWidget; }
	FORCEINLINE void SetContentManager(UWContentManagerBase* pContentManager) { mpContentManager = pContentManager; }

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& inGeometry, const FPointerEvent& inMouseEvent, UDragDropOperation*& outOperation) override;

	/* Properties */
public:

protected:
	UWMainWidget* mpMainWidget;
	UWContentManagerBase* mpContentManager;
};
