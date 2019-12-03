// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Character.h"
#include "WPlayerCharacter.generated.h"

UCLASS()
class PROJECTW_API AWPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Methods */
public:
	AWPlayerCharacter();

	virtual void Tick(float deltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* pPlayerInputComponent) override;

	void DelTargetActor();
	
	/* Get/Set */
	FORCEINLINE class UWInventoryManager* const& GetInventory() const { return mpInventory; }
	FORCEINLINE AActor* const& GetTargetActor() const { return mpTargetActor; }

	FORCEINLINE void SetTargetActor(AActor* pTargetActor) 
	{ 
		mpTargetActor = pTargetActor; 
		WLOG(Warning, TEXT("Player PickupActor Set!!"));
	}

protected:
	virtual void BeginPlay() override;

private:
	void Interact();

	void MoveForward(float newAxisValue);
	void MoveRight(float newAxisValue);
	void LookUp(float newAxisValue);
	void Turn(float newAxisValue);

	/* Properties */
public:	

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* mpWeapon;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AWWeapon* mpCurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* mpSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* mpCamera;
	
private:
	UPROPERTY()
	class AWPlayerController* mpPlayerController;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
	class UWInventoryManager* mpInventory;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	AActor* mpTargetActor;

};