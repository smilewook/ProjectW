// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "GameFramework/Character.h"
#include "WPlayerCharacter.generated.h"


class AWItemEquipment;
class AWPickupActor;
class AWPlayerController;
class UWEquipmentManager;
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

	// 캐릭터 장비
	void SetWeapon(AWItemEquipment* pNewWeapon);
	void SetSecondWeapon(AWItemEquipment* pNewWeapon);

	// 캐릭터 속성
	bool ModifyStatAttribute(EStatAttributeType statType, float value);
	
	/* Get/Set */
	FORCEINLINE UWMainWidget*		const& GetMainWidget() const { return mpMainWidget; }
	FORCEINLINE UWInventoryManager* const& GetInventoryManager() const { return mpInventoryManager; }
	FORCEINLINE UWStatManager*		const& GetStatManager() const { return mpStatManager; }
	FORCEINLINE UWEquipmentManager* const& GetEquipmentManager() const { return mpEquipmentManager; }
	
	FORCEINLINE AWPickupActor*		const& GetTargetActor() const { return mpTargetActor; }

	FORCEINLINE void SetTargetActor(AWPickupActor* pTargetActor) { mpTargetActor = pTargetActor; }

protected:
	virtual void BeginPlay() override;

private:
	void Interact();
	void ToggleMouseCursor();
	void ToggleInventory();
	void ToggleStat();
	void ToggleEquip();

	void MoveForward(float newAxisValue);
	void MoveRight(float newAxisValue);
	void LookUp(float newAxisValue);
	void Turn(float newAxisValue);

	/* Properties */
protected:
	// 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Components | Camera")
	USpringArmComponent* mpSpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components | Camera")
	UCameraComponent* mpCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components | Equip")
	AWItemEquipment* mpCurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Components | Equip")
	USkeletalMeshComponent* mpWeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components | Equip")
	AWItemEquipment* mpCurrentSecondWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = "Components | Equip")
	USkeletalMeshComponent* mpSecondWeaponMesh;
	
	// 컨트롤
	UPROPERTY()
	AWPlayerController* mpPlayerController;

	// 위젯
	UPROPERTY()
	UWMainWidget* mpMainWidget;

	UPROPERTY(VisibleAnywhere, Category = "ContentsManager")
	UWInventoryManager* mpInventoryManager;

	UPROPERTY(VisibleAnywhere, Category = "ContentsManager")
	UWStatManager* mpStatManager;

	UPROPERTY(VisibleAnywhere, Category = "ContentsManager")
	UWEquipmentManager* mpEquipmentManager;

	// 인터렉션
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	AWPickupActor* mpTargetActor;

	

};
