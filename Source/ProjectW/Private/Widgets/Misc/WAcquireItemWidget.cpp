// Fill out your copyright notice in the Description page of Project Settings.


#include "WAcquireItemWidget.h"
#include "Items/WItemBase.h"
#include "Widgets/WMainWidget.h"

#include <Animation/WidgetAnimation.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Kismet/KismetSystemLibrary.h>
#include <MovieScene.h>

#define LOCTEXT_NAMESPACE "Format"


void UWAcquireItemWidget::InitWidget(AWItemBase* pItemClass, int amount, float visibleDuration, class UWMainWidget* pMainWidget)
{
	AssignAnimations();

	if (nullptr != pItemClass)
	{
		mpItemClass = pItemClass;
	}

	mAmount = amount;
	mVisibleDuration = visibleDuration;

	if (nullptr != pMainWidget)
	{
		mpMainWidget = pMainWidget;
	}

	mpIcon->SetBrushFromTexture(pItemClass->GetItemInfo().pIcon);
	mpNameText->SetText(FText::FromName(pItemClass->GetItemInfo().Name));

	FText Format = FText::Format(LOCTEXT("Format", "x{0}"), mAmount);
	mpAmountText->SetText(Format);
}

void UWAcquireItemWidget::AssignAnimations()
{
	UProperty* pProperty = GetClass()->PropertyLink;

	// Ŭ���� ���� ��� �Ӽ����� ���� �ִϸ��̼��� ã�´�.
	while (nullptr != pProperty)
	{
		// ã�� �Ӽ��� ������Ʈ �Ӽ� �϶�
		if (pProperty->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* pObjProperty = Cast<UObjectProperty>(pProperty);

			// ������Ʈ �Ӽ��� ���� �ִϸ��̼��϶�
			if (pObjProperty->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* pObj = pObjProperty->GetObjectPropertyValue_InContainer(this, 0);
				UWidgetAnimation* pWidgetAnim = Cast<UWidgetAnimation>(pObj);

				if (nullptr != pWidgetAnim  && nullptr != pWidgetAnim->MovieScene)
				{
					if (pWidgetAnim->MovieScene->GetFName() == "FadeOut")
					{
						mpFadeOut = pWidgetAnim;
					}
					else if (pWidgetAnim->MovieScene->GetFName() == "FadeIn")
					{
						mpFadeIn = pWidgetAnim;
					}
				}
			}
		}
		// ���� �Ӽ�����
		pProperty = pProperty->PropertyLinkNext;
	}
}

void UWAcquireItemWidget::Show()
{
	//SetVisibility(ESlateVisibility::HitTestInvisible);

	PlayAnimation(mpFadeIn);
	float delayTime = mpFadeIn->GetEndTime();

	FLatentActionInfo latent;
	latent.CallbackTarget = this;
	latent.ExecutionFunction = TEXT("FadeIn");
	latent.Linkage = 1;
	latent.UUID = GetUniqueID();
	UKismetSystemLibrary::Delay(this, delayTime, latent);
}

void UWAcquireItemWidget::FadeIn()
{
	FLatentActionInfo latent;
	latent.CallbackTarget = this;
	latent.ExecutionFunction = TEXT("FadeOut");
	latent.Linkage = 1;
	latent.UUID = GetUniqueID();
	UKismetSystemLibrary::Delay(this, mVisibleDuration, latent);
}

void UWAcquireItemWidget::FadeOut()
{
	PlayAnimation(mpFadeOut);
	float delayTime = mpFadeOut->GetEndTime();

	FLatentActionInfo latent;
	latent.CallbackTarget = this;
	latent.ExecutionFunction = TEXT("Hide");
	latent.Linkage = 1;
	latent.UUID = GetUniqueID();
	UKismetSystemLibrary::Delay(this, delayTime, latent);
}

void UWAcquireItemWidget::Hide()
{
	//SetVisibility(ESlateVisibility::Hidden);
	mpMainWidget->EndAcquireItemMessage();
}

#undef LOCTEXT_NAMESPACE