// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "ProjectWEnums.h"
#include "GameFramework/Actor.h"
#include "WGameStage.generated.h"

UCLASS()
class PROJECTW_API AWGameStage : public AActor
{
	GENERATED_BODY()
	
	/* Method */
public:	
	AWGameStage();

	virtual void OnConstruction(const FTransform& transform) override;

protected:
	virtual void BeginPlay() override;

private:
	void SetState(EStageState newState);

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult &sweepResult);
	
	void OnSpawnEmeny();

	UFUNCTION()
	void OnDestroyedEnemy(AActor* destroyedActor);

	/* Properties */
private:	
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* mpMesh;

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	UBoxComponent* mpTrigger;

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool mIsNoBattle;

	EStageState mCurrentState = EStageState::READY;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float mSpawnEnemyTime;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float mSpawnItemTime;

	FTimerHandle mSpawnEnemyTimerHandle = {};
	FTimerHandle mSpawnItemTimerHandle = {};
};
