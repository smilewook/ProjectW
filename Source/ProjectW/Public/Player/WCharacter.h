// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "GameFramework/Character.h"
#include "WCharacter.generated.h"


UCLASS()
class PROJECTW_API AWCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Method */
public:
	// Sets default values for this character's properties
	AWCharacter();

	ECharacterState GetCharacterState() const;
	void SetCharacterState(ECharacterState newState);
	float GetFinalAttackRange() const;
	float GetFinalAttackDamage() const;

	virtual void Tick(float deltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* pPlayerInputComponent) override;
	virtual float TakeDamage(float damage, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser) override;
	
	bool CanSetWeapon();
	void SetWeapon(class AWWeapon* pNewWeapon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetControlMode(EControlMode controlMode);

private:
	void MoveForward(float newAxisValue);
	void MoveRight(float newAxisValue);
	void LookUp(float newAxisValue);
	void Turn(float newAxisValue);

	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* pmontage, bool bInterrupted);
	void OnAssetLoadCompleted();
	void AttackStartComboState();
	void AttackEndComboState();
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

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* mpSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* mpCamera;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* mpHPBarWidget;

	EControlMode mCurrentControlMode = EControlMode::GTA;
	FVector mDirectionToMove = FVector::ZeroVector;

	float mArmLengthTo = 0.0f;
	FRotator mArmRotationTo = FRotator::ZeroRotator;
	float mArmLengthSpeed = 0.0f;
	float mArmRotationSpeed = 0.0f;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool mIsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool mCanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool mIsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 mCurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 mMaxCombo;

	UPROPERTY()
	class UWCharacterAnimInstance* mCharacterAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float mAttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float mAttackRadius;

	int32 mAssetIndex = 0;

	FSoftObjectPath mCharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> mAssetStreamingHandle;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	ECharacterState mCurrentState;	

	UPROPERTY()
	class AWPlayerController* mpPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, Meta = (AllowPrivateAccess = true))
	float mDeadTimer;

	FTimerHandle mDeadTimerHandle = {};
};
