// Fill out your copyright notice in the Description page of Project Settings.


#include "WCharacterAnimInstance.h"

UWCharacterAnimInstance::UWCharacterAnimInstance()
{
	mCurrentSpeed = 0.0f;
	mIsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		mpAttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UWCharacterAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	// 폰에 접근해서 폰의 속력 값을 얻어온다.
	auto pawn = TryGetPawnOwner();
	if (::IsValid(pawn))
	{
		mCurrentSpeed = pawn->GetVelocity().Size();
		auto character = Cast<ACharacter>(pawn);
		if (nullptr != character)
		{
			mIsInAir = character->GetMovementComponent()->IsFalling();
		}
	}
}

void UWCharacterAnimInstance::PlayAttackMontage()
{
	Montage_Play(mpAttackMontage, 1.0f);
}

void UWCharacterAnimInstance::JumpToAttackMontageSection(int32 newSection)
{
	WCHECK(Montage_IsPlaying(mpAttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(newSection), mpAttackMontage);
}

void UWCharacterAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UWCharacterAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UWCharacterAnimInstance::GetAttackMontageSectionName(int32 section)
{
	WCHECK(FMath::IsWithinInclusive<int32>(section, 1, 2), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), section));
}
