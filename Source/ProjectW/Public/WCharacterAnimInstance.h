// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "Animation/AnimInstance.h"
#include "WCharacterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate)
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate)

/**
 * 
 */
UCLASS()
class PROJECTW_API UWCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UWCharacterAnimInstance();

	virtual void NativeUpdateAnimation(float deltaSeconds) override;
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 newSection);

public:
	FOnNextAttackCheckDelegate	OnNextAttackCheck;
	FOnAttackHitCheckDelegate	OnAttackHitCheck;

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 section);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float mCurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool mIsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* mpAttackMontage;
	
};

