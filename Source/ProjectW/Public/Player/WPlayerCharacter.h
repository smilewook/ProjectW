// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Character.h"
#include "WPlayerCharacter.generated.h"

class AWPlayerController;
class AWWeapon;

class UWInventoryManager;
class UWMainWidget;


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
	FORCEINLINE UWMainWidget* const& GetMainWidget() const { return mpMainWidget; }
	FORCEINLINE UWInventoryManager* GetInventory() const { return mpInventory; }
	
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
	void ToggleInventory();

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
	AWWeapon* mpCurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* mpSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* mpCamera;
	
/*private:*/
	UPROPERTY()
	AWPlayerController* mpPlayerController;

	UPROPERTY()
	UWMainWidget* mpMainWidget;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UWInventoryManager* mpInventory;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	AActor* mpTargetActor;

};
