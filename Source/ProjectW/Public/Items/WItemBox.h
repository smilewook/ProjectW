// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Actor.h"
#include "WItemBox.generated.h"


UCLASS()
class PROJECTW_API AWItemBox : public AActor
{
	GENERATED_BODY()
	
	/* Method */
public:	
	// Sets default values for this actor's properties
	AWItemBox();

	// Called every frame
	virtual void Tick(float deltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* pParticleSystem);

	/* Properties */
public:	
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TSubclassOf<class AWWeapon> WeaponItemClass;


};
