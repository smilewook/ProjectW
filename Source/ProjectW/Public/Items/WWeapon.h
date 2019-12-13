// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Actor.h"
#include "WWeapon.generated.h"


UCLASS()
class PROJECTW_API AWWeapon : public AActor
{
	GENERATED_BODY()
	
	/* Method */
public:	
	AWWeapon();

	float GetAttackRange() const;
	float GetAttackDamage() const;
	float GetAttackModifier() const;

protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float mAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float mAttackDamageMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float mAttackDamageMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float mAttackModifierMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float mAttackModifierMax;
	
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float mAttackDamage;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = Attack)
	float mAttackModifier;
};
