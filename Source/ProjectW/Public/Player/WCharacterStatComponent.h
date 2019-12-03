// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Components/ActorComponent.h"
#include "WCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTW_API UWCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

	/* Method */
public:	
	// Sets default values for this component's properties
	UWCharacterStatComponent();

	void SetNewLevel(int32 newLevel);
	void SetDamage(float newDamage);
	void SetHP(float newHP);
	float GetAttack();
	float GetHPRatio();
	int32 GetDropExp();

	FOnHPIsZeroDelegate		OnHPIsZero;
	FOnHPChangedDelegate	OnHPChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	/* Properties */
public:	

private:	
	struct FWCharacterData* mpCurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = stat, Meta = (AllowPrivateAccess = true))
	int32 mLevel;
		
	UPROPERTY(Transient, VisibleInstanceOnly, Category = stat, Meta = (AllowPrivateAccess = true))
	float mCurrentHP;
};
