// Fill out your copyright notice in the Description page of Project Settings.


#include "WStatManager.h"
#include "WGameInstance.h"
#include "Player/WPlayerCharacter.h"
#include "Player/WPlayerState.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/Player/WHUDWidget.h"
#include "Widgets/Stat/WStatWidget.h"
#include "Widgets/Stat/WStatLabelWidget.h"


UWStatManager::UWStatManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	mStats.Empty();
	for (int32 i = 0; i < (int32)EStatAttributeType::StatAttribute_Max; i++)
	{
		mStats.Add(EStatAttributeType(i), FStatInfo());
	}

	mLevel = 1;
}

void UWStatManager::InitManager(UWContentWidgetBase* pWidget)
{
	UWContentManagerBase::InitManager(pWidget);

	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(GetOwner());
	mpPlayerState = Cast<AWPlayerState>(pPlayer->GetPlayerState());
	mpPlayerState->OnPlayerStateChanged.AddUObject(this, &UWStatManager::UpdatePlayerState);

	// 스탯 위젯 초기화.
	mpStatLabelWidgets.Empty();

	Cast<UWStatWidget>(mpWidget)->CreateStatAttribute();

	UpdateNewLevel(mLevel);	
}

void UWStatManager::UpdateManager()
{
	// 초기 캐릭터 스탯 설정.
	for (int32 i = 0; i < (int32)EStatAttributeType::StatAttribute_Max; i++)
	{
		mpStatLabelWidgets[i]->UpdateWidget(mStats[(EStatAttributeType)i]);

		UpdateStatAttribute((EStatAttributeType)i, mStats[(EStatAttributeType)i].CurrentValue, mStats[(EStatAttributeType)i].MaxValue);
	}
}

void UWStatManager::AddStatAttribute(UWStatLabelWidget* const& pStatLabelWidget)
{
	mpStatLabelWidgets.Add(pStatLabelWidget);
}

void UWStatManager::UpdateNewLevel(int32 newLevel)
{
	// 레벨에 따른 기본 스탯 값들을 가져옴.
	auto gameInstance = Cast<UWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	WCHECK(nullptr != gameInstance);
	mpCurrentStatData = gameInstance->GetCharacterData(newLevel);
	if (nullptr != mpCurrentStatData)
	{
		mLevel = newLevel;

		mStats[EStatAttributeType::StatAttribute_Level].MaxValue = mLevel;
		ModifyMaxStatAttribute(EStatAttributeType::StatAttribute_Exp, mpCurrentStatData->NextExp);
		ModifyMaxStatAttribute(EStatAttributeType::StatAttribute_HP, mpCurrentStatData->MaxHP);
		ModifyMaxStatAttribute(EStatAttributeType::StatAttribute_MP, mpCurrentStatData->MaxMP);
		ModifyMaxStatAttribute(EStatAttributeType::StatAttribute_Attack, mpCurrentStatData->Attack);

		mStats[EStatAttributeType::StatAttribute_Level].CurrentValue = mLevel;
		mStats[EStatAttributeType::StatAttribute_Exp].CurrentValue = mpPlayerState->GetExp();
		ModifyCurrentStatAttribute(EStatAttributeType::StatAttribute_HP, mpCurrentStatData->MaxHP);
		ModifyCurrentStatAttribute(EStatAttributeType::StatAttribute_MP, mpCurrentStatData->MaxMP);		

		UpdateManager();
	}
	else
	{
		WLOG(Error, TEXT("Level (%d) data doesnt exist"), newLevel);
	}
}

void UWStatManager::UpdateDamage(float newDamage)
{
	ModifyCurrentStatAttribute(EStatAttributeType::StatAttribute_HP, -newDamage);
}

void UWStatManager::UpdateHP(float currentHP, float maxHP)
{
	//WLOG(Warning, TEXT("UpdateHP : (%f / %f)"), currentHP, maxHP);
	
	mCurrentHP = currentHP;
	mMaxHP = maxHP;
	OnHPChanged.Broadcast();

	if (mCurrentHP < KINDA_SMALL_NUMBER)
	{
		mCurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void UWStatManager::UpdateMP(float currentMP, float maxMP)
{
	//WLOG(Warning, TEXT("UpdateMP : (%f / %f)"), currentMP, maxMP);

	mCurrentMP = currentMP;
	mMaxMP = maxMP;
	OnMPChanged.Broadcast();
}

void UWStatManager::UpdatePlayerState()
{
	if (mLevel != mpPlayerState->GetCharacterLevel())
	{
		mLevel = mpPlayerState->GetCharacterLevel();
		UpdateNewLevel(mLevel);
	}
	else
	{
		mStats[EStatAttributeType::StatAttribute_Exp].CurrentValue = mpPlayerState->GetExp();
		mpStatLabelWidgets[(uint8)EStatAttributeType::StatAttribute_Exp]->UpdateWidget(mStats[EStatAttributeType::StatAttribute_Exp]);
	}
}

bool UWStatManager::ModifyCurrentStatAttribute(const EStatAttributeType& statType, float inValue)
{
	// 아이템 사용에 의한 스탯 데이터 수정.
	if (mpStatLabelWidgets.IsValidIndex((uint8)statType))
	{
		//WLOG(Warning, TEXT("UWStatManager::ModifyCurrentStatAttribute() type : %d, value : %f"), statType, inValue);
		if (mStats[statType].CurrentValue + inValue >= mStats[statType].MaxValue)
		{
			mStats[statType].CurrentValue = mStats[statType].MaxValue;
		}
		else if (mStats[statType].CurrentValue + inValue <= 0.0f)
		{
			mStats[statType].CurrentValue = 0.0f;
		}
		else
		{
			mStats[statType].CurrentValue += inValue;
		}

		UpdateStatAttribute(statType, mStats[statType].CurrentValue, mStats[statType].MaxValue);
		mpStatLabelWidgets[(uint8)statType]->UpdateWidget(mStats[statType]);

		return true;
	}

	return false;
}

bool UWStatManager::ModifyMaxStatAttribute(const EStatAttributeType& statType, float inValue)
{
	// 아이템 사용에 의한 스탯 데이터 수정.
	if (mpStatLabelWidgets.IsValidIndex((uint8)statType))
	{
		//WLOG(Warning, TEXT("UWStatManager::ModifyMaxStatAttribute() type : %d, value : %f"), statType, inValue);
		mStats[statType].MaxValue += inValue;
		if (mStats[statType].MaxValue <= mStats[statType].CurrentValue)
		{
			mStats[statType].MaxValue = mStats[statType].CurrentValue;
		}
		
		UpdateStatAttribute(statType, mStats[statType].CurrentValue, mStats[statType].MaxValue);
		mpStatLabelWidgets[(uint8)statType]->UpdateWidget(mStats[statType]);

		return true;
	}

	return false;
}

void UWStatManager::UpdateStatAttribute(EStatAttributeType type, float currentValue, float maxValue)
{
	switch (type)
	{
	case EStatAttributeType::StatAttribute_HP:
		UpdateHP(currentValue, maxValue);
		break;
	case EStatAttributeType::StatAttribute_MP:
		UpdateMP(currentValue, maxValue);
		break;
	default:
		break;
	}
}
