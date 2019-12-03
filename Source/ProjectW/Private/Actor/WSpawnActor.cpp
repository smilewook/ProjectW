// Fill out your copyright notice in the Description page of Project Settings.


#include "WSpawnActor.h"
#include "WEnemy.h"
#include "Kismet/KismetMathLibrary.h"


AWSpawnActor::AWSpawnActor()
{
 	PrimaryActorTick.bCanEverTick = false;

	mpSpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SPAWNVOLUME"));
	RootComponent = mpSpawnVolume;

	mSpawnEnemyClass = AWEnemy::StaticClass();
	mSpawnTime = 2.0f;
	mMaxSpawnCount = 1;
}

bool AWSpawnActor::Spawn()
{
	WLOG(Warning, TEXT("AWSpawnActor::Spawn() : %d"), mSpawnEnemies.Num());
	FTimerHandle hTimer;
	int index = 0;
	GetWorld()->GetTimerManager().SetTimer(hTimer, [&, index] {
		FVector spawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), mpSpawnVolume->GetScaledBoxExtent());
		AWEnemy* pEnemy = GetWorld()->SpawnActor<AWEnemy>(mSpawnEnemyClass, spawnLoc, FRotator::ZeroRotator);
		pEnemy->InitEnemy(spawnLoc, this, index);
		GetWorld()->GetTimerManager().ClearTimer(hTimer);
	}, mSpawnTime, false);
	
	return false;
}

void AWSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	//WLOG(Warning, TEXT("AWSpawnActor::BeginPlay()"));
	for (int i = 0; i < mMaxSpawnCount; ++i)
	{
		FVector spawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), mpSpawnVolume->GetScaledBoxExtent());
		FActorSpawnParameters params;
		params.OverrideLevel = GetLevel();
		AWEnemy* pEnemy = GetWorld()->SpawnActor<AWEnemy>(mSpawnEnemyClass, spawnLoc, FRotator::ZeroRotator, params);
		pEnemy->InitEnemy(spawnLoc, this, i);
		//mSpawnEnemies.Add(pEnemy);
	}
}

