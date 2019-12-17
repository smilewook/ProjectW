// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "GameFramework/Character.h"
#include "WPlayerCharacter.generated.h"


class AWPickupActor;
class AWPlayerController;
class AWWeapon;

class UWInventoryManager;
class UWStatManager;
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

	// 캐릭터 속성
	bool MotifyStatAttribute(EStatAttributeType statType, float value);
	
	/* Get/Set */
	FORCEINLINE UWMainWidget* const& GetMainWidget() const { return mpMainWidget; }
	FORCEINLINE UWInventoryManager* const& GetInventoryManager() const { return mpInventoryManager; }
	FORCEINLINE UWStatManager* const& GetStatManager() const { return mpStatManager; }
	
	FORCEINLINE AWPickupActor* const& GetTargetActor() const { return mpTargetActor; }

	FORCEINLINE void SetTargetActor(AWPickupActor* pTargetActor) { mpTargetActor = pTargetActor; }

protected:
	virtual void BeginPlay() override;

private:
	void Interact();
	void ToggleMouseCursor();
	void ToggleInventory();
	void ToggleStat();

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

	UPROPERTY(VisibleAnywhere, Category = "ContentsManager")
	UWInventoryManager* mpInventoryManager;

	UPROPERTY(VisibleAnywhere, Category = "ContentsManager")
	UWStatManager* mpStatManager;

	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	AWPickupActor* mpTargetActor;

};
