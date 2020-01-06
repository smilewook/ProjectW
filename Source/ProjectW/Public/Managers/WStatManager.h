// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Managers/WContentManagerBase.h"
#include "WStatManager.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPChangedDelegate);

class AWPlayerState;

class UWStatWidget;
class UWStatLabelWidget;


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTW_API UWStatManager : public UWContentManagerBase
{
	GENERATED_BODY()
	
	/* Methods */
public:
	UWStatManager();

	FOnHPIsZeroDelegate		OnHPIsZero;
	FOnHPChangedDelegate	OnHPChanged;
	FOnMPChangedDelegate	OnMPChanged;

	virtual void InitManager(UWContentWidgetBase* pWidget) override;
	virtual void UpdateManager() override;

	void AddStatAttribute(UWStatLabelWidget* const& pStatLabelWidget);

	// æ˜µ•¿Ã∆Æ Ω∫≈»
	
	void UpdateNewLevel(int32 newLevel);
	void UpdateDamage(float newDamage);
	void UpdateHP(float currentHP, float maxHP);
	void UpdateMP(float currentMP, float maxMP);
	void UpdatePlayerState();

	// Ω∫≈» ∫Ø∞Ê
	bool ModifyCurrentStatAttribute(const EStatAttributeType& statType, float value);
	bool ModifyMaxStatAttribute(const EStatAttributeType& statType, float value);

	/* Get/Set */
	FORCEINLINE const TMap<EStatAttributeType, FStatInfo>& GetStats() const { return mStats; }
	FORCEINLINE const FStatInfo& GetStat(EStatAttributeType type) const { return mStats[type]; }

	FORCEINLINE const float GetAttack() const { return mStats[EStatAttributeType::StatAttribute_Attack].MaxValue; }
	FORCEINLINE const float GetHPRatio() const { return (mMaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (mCurrentHP / mMaxHP); }
	FORCEINLINE const float GetMPRatio() const { return (mMaxMP < KINDA_SMALL_NUMBER) ? 0.0f : (mCurrentMP / mMaxMP); }

protected:
	void UpdateStatAttribute(EStatAttributeType type, float currentValue, float maxValue);

	/* Properties */
protected:
	struct FWCharacterData* mpCurrentStatData = nullptr;

	UPROPERTY()
	AWPlayerState* mpPlayerState;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TMap<EStatAttributeType, FStatInfo> mStats;

	UPROPERTY()
	TArray<UWStatLabelWidget*> mpStatLabelWidgets;

private:
	UPROPERTY(EditInstanceOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	int32 mLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float mCurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float mMaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float mCurrentMP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "State", Meta = (AllowPrivateAccess = true))
	float mMaxMP;
};
