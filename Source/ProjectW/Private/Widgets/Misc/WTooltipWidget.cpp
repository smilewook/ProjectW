// Fill out your copyright notice in the Description page of Project Settings.


#include "WTooltipWidget.h"
#include "ProjectWEnums.h"
#include "Items/WItemBase.h"
#include "Widgets/WMainWidget.h"

#include <WidgetTree.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>

#define LOCTEXT_NAMESPACE "Format"


void UWTooltipWidget::InitWidget(UWMainWidget* pMainWidget, UWContentManagerBase* pContentManager)
{
	mpMainWidget = pMainWidget;

	for (int32 i = 0; i < (int32)EStatAttributeType::StatAttribute_Max; ++i)
	{
		UTextBlock* pTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		pTextBlock->SetVisibility(ESlateVisibility::Collapsed);
		mpStats->AddChildToVerticalBox(pTextBlock);
	}
}

void UWTooltipWidget::UpdateData(AWItemBase* pItemClass)
{
	FItemInfo itemInfo = pItemClass->GetItemInfo();

	// 아이콘.
	mpIcon->SetBrushFromTexture(itemInfo.pIcon);

	// 아이템 이름.
	mpNameText->SetText(FText::FromName(itemInfo.Name));

	// 아이템 설명.
	FString descriptionStr = itemInfo.Description.ToString().Replace(L"/n", L"\n");
	mpDescriptionText->SetText(FText::FromString(descriptionStr));

	// 아이템 속성.
	if (itemInfo.ItemStats.Num() < 1)
	{
		mpStatSection->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		for (int32 i = 0; i < (int32)EStatAttributeType::StatAttribute_Max; ++i)
		{
			if (itemInfo.ItemStats.Contains(EStatAttributeType(i)))
			{
				UTextBlock* pTextBlock = Cast<UTextBlock>(mpStats->GetChildAt(i));

				FString statTypeStr = CONVERT_DISPLAYNAME_TO_STRING(L"EStatAttributeType", EStatAttributeType(i));
				FText Format = FText::Format(LOCTEXT("Format", "{0} : {1}"), FText::FromString(statTypeStr), itemInfo.ItemStats[EStatAttributeType(i)]);
				pTextBlock->SetText(Format);
				pTextBlock->Font.Size = 17;
				pTextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				UTextBlock* pTextBlock = Cast<UTextBlock>(mpStats->GetChildAt(i));
				pTextBlock->SetVisibility(ESlateVisibility::Collapsed);
			}

		}
		mpStatSection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

#undef LOCTEXT_NAMESPACE
