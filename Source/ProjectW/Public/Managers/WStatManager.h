// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectWEnums.h"
#include "ProjectWStructure.h"
#include "Managers/WContentManagerBase.h"
#include "WStatManager.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

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

	virtual void InitManager(UWContentWidgetBase* pWidget) override;
	virtual void UpdateManager() override;

	void UpdateNewLevel(int32 newLevel);
	void UpdateDamage(float newDamage);
	void UpdateHP(float newHP);

	bool ModifyStatAttribute(const EStatAttributeType& statType, float value);

	void SetStatAttribute(UWStatLabelWidget* const& pStatLabelWidget);

	/* Get/Set */
	float GetAttack() const;
	float GetHPRatio() const;
	int32 GetDropExp() const;
	FORCEINLINE const TMap<EStatAttributeType, FStatInfo>& GetStats() const { return mStats; }
	FORCEINLINE const FStatInfo& GetStat(EStatAttributeType type) const { return mStats[type]; }

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	/* Properties */
protected:
	struct FWCharacterData* mpCurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = stat, Meta = (AllowPrivateAccess = true))
	int32 mLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = stat, Meta = (AllowPrivateAccess = true))
	float mCurrentHP;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	TMap<EStatAttributeType, FStatInfo> mStats;

	TArray<UWStatLabelWidget*> mpStatLabelWidgets;

};
