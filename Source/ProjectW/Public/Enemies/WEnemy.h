// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "GameFramework/Character.h"
#include "WEnemy.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);


UCLASS()
class PROJECTW_API AWEnemy : public ACharacter
{
	GENERATED_BODY()
	
	/* Method */
public:
	AWEnemy();

	void InitEnemy(const FVector& location, class AWSpawnActor* pSpawnActor, int32 inID);

	int32 GetID() const;
	ECharacterState GetEnemyState() const;
	void SetEnemyState(ECharacterState newState);
	int32 GetExp() const;
	float GetFinalAttackRange() const;

	virtual void Tick(float deltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* pPlayerInputComponent) override;
	virtual float TakeDamage(float damage, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser) override;

	void SetWeapon(class AWWeapon* pNewWeapon);
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* pmontage, bool bInterrupted);

protected:
	virtual void BeginPlay() override;

private:
	void OnAssetLoadCompleted();
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

private:
	UPROPERTY()
	class UWCharacterAnimInstance* mCharacterAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float mAttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float mAttackRadius;

	int32 mAssetIndex = 0;

	FSoftObjectPath mEnemyAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> mAssetStreamingHandle;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	int mID;

	UPROPERTY()
	class AWSpawnActor* mpSpawnActor;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	ECharacterState mCurrentState;

	UPROPERTY()
	class AWEnemyAIController* mpEnemyAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = true))
	float mDeadTimer;

	FTimerHandle mDeadTimerHandle = {};
};
