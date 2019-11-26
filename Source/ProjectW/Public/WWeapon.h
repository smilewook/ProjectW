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
	// Sets default values for this actor's properties
	AWWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Properties */
public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	
};
