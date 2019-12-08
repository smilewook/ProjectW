// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Actor.h"
#include "WSpawnActor.generated.h"

UCLASS()
class PROJECTW_API AWSpawnActor : public AActor
{
	GENERATED_BODY()
	
	/* Method */
public:	
	AWSpawnActor();

	bool Spawn();

protected:
	virtual void BeginPlay() override;

	/* Properties */
public:	
	

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* mpSpawnVolume;

	// #. 스폰할 적 클래스.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<class AWEnemy> mSpawnEnemyClass;

	// #. 최대 스폰 갯수.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	uint8 mMaxSpawnCount;

	// #. 스폰 시간.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	uint8 mSpawnTime;

	// #. 적군 목록.
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<AWEnemy*> mSpawnEnemies;

};
