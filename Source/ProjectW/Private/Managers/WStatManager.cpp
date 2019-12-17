// Fill out your copyright notice in the Description page of Project Settings.


#include "WStatManager.h"
#include "WGameInstance.h"
#include "Widgets/Stat/WStatWidget.h"
#include "Widgets/Stat/WStatLabelWidget.h"


UWStatManager::UWStatManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	mStats.Empty();
	for (int32 i = 0; i < (int32)EStatAttributeType::EStatAttribute_Max; i++)
	{
		mStats.Add(EStatAttributeType(i), FStatInfo());
	}

	mLevel = 1;
}

void UWStatManager::InitManager(UWContentWidgetBase * pWidget)
{
	UWContentManagerBase::InitManager(pWidget);

	// 스탯 위젯 초기화.
	mpStatLabelWidgets.Empty();

	Cast<UWStatWidget>(mpWidget)->CreateStatAttribute();

	UpdateNewLevel(mLevel);
}

void UWStatManager::UpdateManager()
{
	// something like that
}

void UWStatManager::BeginPlay()
{
	Super::BeginPlay();
}

void UWStatManager::InitializeComponent()
{
	Super::InitializeComponent();
}

void UWStatManager::UpdateNewLevel(int32 newLevel)
{
	auto gameInstance = Cast<UWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	WCHECK(nullptr != gameInstance);
	mpCurrentStatData = gameInstance->GetCharacterData(newLevel);
	if (nullptr != mpCurrentStatData)
	{
		mLevel = newLevel;
		UpdateHP(mpCurrentStatData->MaxHP);
	}
	else
	{
		WLOG(Error, TEXT("Level (%d) data doesnt exist"), newLevel);
	}
}

void UWStatManager::UpdateDamage(float newDamage)
{
	WCHECK(nullptr != mpCurrentStatData);
	UpdateHP(FMath::Clamp<float>(mCurrentHP - newDamage, 0.0f, mpCurrentStatData->MaxHP));
}

void UWStatManager::UpdateHP(float newHP)
{
	WLOG(Warning, TEXT("SetHP : %f"), newHP);
	mCurrentHP = newHP;
	OnHPChanged.Broadcast();

	if (mCurrentHP < KINDA_SMALL_NUMBER)
	{
		mCurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

bool UWStatManager::ModifyStatAttribute(const EStatAttributeType& statType, float value)
{
	// 아이템 사용에 의한 스탯 데이터 수정.
	if (mpStatLabelWidgets.IsValidIndex((uint8)statType))
	{
		WLOG(Warning, TEXT("UWStatManager::ModifyStatAttribute() type : %d, value : %f"), statType, value);
		mStats[statType].CurrentValue += value;

		mpStatLabelWidgets[(uint8)statType]->UpdateWidget(mStats[statType]);

		return true;
	}

	return false;
}

void UWStatManager::SetStatAttribute(UWStatLabelWidget* const& pStatLabelWidget)
{
	mpStatLabelWidgets.Add(pStatLabelWidget);
}

float UWStatManager::GetAttack() const
{
	WCHECK(nullptr != mpCurrentStatData, 0.0f);
	return mpCurrentStatData->Attack;
}

float UWStatManager::GetHPRatio() const
{
	WCHECK(nullptr != mpCurrentStatData, 0.0f);

	return (mpCurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (mCurrentHP / mpCurrentStatData->MaxHP);
}

int32 UWStatManager::GetDropExp() const
{
	return mpCurrentStatData->DropExp;
}
