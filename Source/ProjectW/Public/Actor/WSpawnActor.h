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

	// #. ������ �� Ŭ����.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	TSubclassOf<class AWEnemy> mSpawnEnemyClass;

	// #. �ִ� ���� ����.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	uint8 mMaxSpawnCount;

	// #. ���� �ð�.
	UPROPERTY(EditAnywhere, Category = "Configuration")
	uint8 mSpawnTime;

	// #. ���� ���.
	UPROPERTY(VisibleAnywhere, Category = "Configuration")
	TArray<AWEnemy*> mSpawnEnemies;

};
