// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Components/ActorComponent.h"
#include "WCharacterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

struct FWCharacterData;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTW_API UWCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

	/* Method */
public:	
	// Sets default values for this component's properties
	UWCharacterStatComponent();

	FOnHPIsZeroDelegate		OnHPIsZero;
	FOnHPChangedDelegate	OnHPChanged;

	/* Get/Set */
	void SetNewLevel(int32 newLevel);
	void SetDamage(float newDamage);
	void SetHP(float newHP);
	float GetAttack();
	float GetHPRatio();
	int32 GetDropExp();
	
protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	/* Properties */
public:	

private:	
	FWCharacterData* mpCurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = stat, Meta = (AllowPrivateAccess = true))
	int32 mLevel;
		
	UPROPERTY(Transient, VisibleInstanceOnly, Category = stat, Meta = (AllowPrivateAccess = true))
	float mCurrentHP;
};
