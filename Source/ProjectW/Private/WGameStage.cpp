// Fill out your copyright notice in the Description page of Project Settings.


#include "WGameStage.h"
#include "WCharacter.h"
#include "WEnemy.h"
#include "WGameMode.h"
#include "WItemBox.h"
#include "WPlayerController.h"


AWGameStage::AWGameStage()
{
 	PrimaryActorTick.bCanEverTick = false;

	mpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = mpMesh;

	FString assetPath = TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Floors/StaticMesh/SM_Plains_Floors_Flat01.SM_Plains_Floors_Flat01");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(*assetPath);
	if (MESH.Succeeded())
	{
		mpMesh->SetStaticMesh(MESH.Object);
	}
	else
	{
		WLOG(Error, TEXT("failed to load asset: %s"), *assetPath);
	}

	mpTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	mpTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 10.0f));
	mpTrigger->SetupAttachment(RootComponent);
	mpTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
	mpTrigger->SetCollisionProfileName(TEXT("SpawnTrigger"));

	mpTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWGameStage::OnTriggerBeginOverlap);

	mIsNoBattle = false;
	mSpawnEnemyTime = 2.0f;
	mSpawnItemTime = 4.0f;
}

void AWGameStage::OnConstruction(const FTransform& tsransform)
{
	Super::OnConstruction(tsransform);

	SetState(mIsNoBattle ? EStageState::COMPLETE : EStageState::READY);
}

// Called when the game starts or when spawned
void AWGameStage::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(mIsNoBattle ? EStageState::COMPLETE : EStageState::READY);
}

void AWGameStage::SetState(EStageState newState)
{
	switch (newState)
	{
	case EStageState::READY:
		WLOG(Warning, TEXT("READY"));
		mpTrigger->SetCollisionProfileName(TEXT("SpawnTrigger"));
		break;

	case EStageState::BATTLE:
		WLOG(Warning, TEXT("BATTLE"));
		mpTrigger->SetCollisionProfileName(TEXT("NoCollision"));

		GetWorld()->GetTimerManager().SetTimer(mSpawnEnemyTimerHandle,
			FTimerDelegate::CreateUObject(this, &AWGameStage::OnSpawnEmeny), mSpawnEnemyTime, false);

		GetWorld()->GetTimerManager().SetTimer(mSpawnItemTimerHandle,
			FTimerDelegate::CreateLambda([this]() -> void {
			FVector2D randomXY = FMath::RandPointInCircle(600.0f);
			GetWorld()->SpawnActor<AWItemBox>(GetActorLocation() + FVector(randomXY, 30.0f), FRotator::ZeroRotator);
		}), mSpawnItemTime, false);
		break;

	case EStageState::COMPLETE:
		WLOG(Warning, TEXT("COMPLETE"));
		mpTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		break;
	}
}

void AWGameStage::OnTriggerBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult &sweepResult)
{
	if (mCurrentState == EStageState::READY)
	{
		SetState(EStageState::BATTLE);
	}
}

void AWGameStage::OnSpawnEmeny()
{
	GetWorld()->GetTimerManager().ClearTimer(mSpawnEnemyTimerHandle);
	auto enemy = GetWorld()->SpawnActor<AWEnemy>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (nullptr != enemy)
	{
		enemy->OnDestroyed.AddDynamic(this, &AWGameStage::OnDestroyedEnemy);
	}
}

void AWGameStage::OnDestroyedEnemy(AActor* destroyedActor)
{
	auto enemy = Cast<AWEnemy>(destroyedActor);
	WCHECK(nullptr != enemy);

	auto playerController = Cast<AWPlayerController>(enemy->LastHitBy);
	WCHECK(nullptr != playerController);

	auto gameMode = Cast<AWGameMode>(GetWorld()->GetAuthGameMode());
	WCHECK(nullptr != gameMode);
	gameMode->AddScore(playerController);

	SetState(EStageState::COMPLETE);
}

