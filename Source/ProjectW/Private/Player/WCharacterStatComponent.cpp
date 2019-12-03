// Fill out your copyright notice in the Description page of Project Settings.


#include "WCharacterStatComponent.h"
#include "WGameInstance.h"


// Sets default values for this component's properties
UWCharacterStatComponent::UWCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	mLevel = 1;
}

// Called when the game starts
void UWCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(mLevel);
}

void UWCharacterStatComponent::SetNewLevel(int32 newLevel)
{
	auto gameInstance = Cast<UWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	WCHECK(nullptr != gameInstance);
	mpCurrentStatData = gameInstance->GetCharacterData(newLevel);
	if (nullptr != mpCurrentStatData)
	{
		mLevel = newLevel;
		SetHP(mpCurrentStatData->MaxHP);
	}
	else
	{
		WLOG(Error, TEXT("Level (%d) data doesnt exist"), newLevel);
	}
}

void UWCharacterStatComponent::SetDamage(float newDamage)
{
	WCHECK(nullptr != mpCurrentStatData);
	SetHP(FMath::Clamp<float>(mCurrentHP - newDamage, 0.0f, mpCurrentStatData->MaxHP));
}

void UWCharacterStatComponent::SetHP(float newHP)
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

float UWCharacterStatComponent::GetAttack()
{
	WCHECK(nullptr != mpCurrentStatData, 0.0f);
	return mpCurrentStatData->Attack;
}

float UWCharacterStatComponent::GetHPRatio()
{
	WCHECK(nullptr != mpCurrentStatData, 0.0f);

	return (mpCurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (mCurrentHP / mpCurrentStatData->MaxHP);
}

int32 UWCharacterStatComponent::GetDropExp()
{
	return mpCurrentStatData->DropExp;
}

