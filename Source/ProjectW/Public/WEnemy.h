// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Character.h"
#include "WEnemy.generated.h"

UCLASS()
class PROJECTW_API AWEnemy : public ACharacter
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWEnemy();
	virtual void Tick(float deltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* pPlayerInputComponent) override;
	virtual float TakeDamage(float damage, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser) override;

	void SetWeapon(class AWWeapon* pNewWeapon);


protected:
	virtual void BeginPlay() override;

private:
	void Attack();
	void AttackCheck();

	/* Properties */
public:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UWCharacterStatComponent* CharacterStat;

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* mpWeapon;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AWWeapon* mpCurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* mpHPBarWidget;

	FVector mDirectionToMove = FVector::ZeroVector;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool mIsAttacking;

	UPROPERTY()
	class UWCharacterAnimInstance* mCharacterAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float mAttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float mAttackRadius;

};
