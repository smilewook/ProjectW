// Fill out your copyright notice in the Description page of Project Settings.


#include "WEnemy.h"
#include "WEnemyAIController.h"
#include "WGameInstance.h"
#include "Actors/WSpawnActor.h"
#include "Items/WWeapon.h"
#include "Player/WCharacterAnimInstance.h"
#include "Player/WCharacterStatComponent.h"
#include "Player/WPlayerController.h"
#include "Widgets/WCharacterWidget.h"

#include "WCharacterSetting.h"

#include <DrawDebugHelpers.h>
#include <Components/WidgetComponent.h>


// Sets default values
AWEnemy::AWEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterStat = CreateDefaultSubobject<UWCharacterStatComponent>(TEXT("CHARACTERSTAT"));
	mpHPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGETENEMY"));

	mpHPBarWidget->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	// 스켈레탈 메시
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CHARACTER_MESH(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Robo.SK_CharM_Robo"));
	if (CHARACTER_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CHARACTER_MESH.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애니메이션 인스턴스
	static ConstructorHelpers::FClassFinder<UAnimInstance> CHARACTER_ANIM(TEXT("/Game/Animations/CharacterAnimBP.CharacterAnimBP_C"));
	if (CHARACTER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CHARACTER_ANIM.Class);
	}

	// 무브먼트
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;

	// 콜리전 프리셋
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("WCharacter"));
	// 공격 범위 디버깅
	mAttackRange = 80.0f;
	mAttackRadius = 50.0f;

	// UIWidget - HPBar.
	mpHPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	mpHPBarWidget->SetWidgetSpace(EWidgetSpace::Screen); // 항상 스크린을 보도록
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBAR(TEXT("/Game/Widgets/WB_HPBar.WB_HPBar_C"));
	if (UI_HPBAR.Succeeded())
	{
		mpHPBarWidget->SetWidgetClass(UI_HPBAR.Class);
		mpHPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	// AI controller
	AIControllerClass = AWEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 캐릭터 에셋
	mAssetIndex = 4;

	// 로딩 전 상태
	SetActorHiddenInGame(true);
	mpHPBarWidget->SetHiddenInGame(true);
	bCanBeDamaged = false;

	mDeadTimer = 4.0f;
}

void AWEnemy::InitEnemy(const FVector& location, AWSpawnActor* pSpawnActor, int inID)
{
	SetActorLocation(location);
	mpSpawnActor = pSpawnActor;
	mID = inID;
}

int32 AWEnemy::GetID() const
{
	return mID;
}

ECharacterState AWEnemy::GetEnemyState() const
{
	return mCurrentState;
}

void AWEnemy::SetEnemyState(ECharacterState newState)
{
	WCHECK(mCurrentState != newState);
	mCurrentState = newState;

	switch (mCurrentState)
	{
	case ECharacterState::LOADING:
	{
		SetActorHiddenInGame(true);
		mpHPBarWidget->SetHiddenInGame(true);
		bCanBeDamaged = false;
		break;
	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		mpHPBarWidget->SetHiddenInGame(false);
		bCanBeDamaged = true;

		CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
			SetEnemyState(ECharacterState::DEAD);
		});

		auto characterWidget = Cast<UWCharacterWidget>(mpHPBarWidget->GetUserWidgetObject());
		WCHECK(nullptr != characterWidget);
		characterWidget->BindCharacterStat(CharacterStat);

		mpEnemyAIController->PlayAI();
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		mpHPBarWidget->SetHiddenInGame(true);
		mCharacterAnim->SetDeadAnim();
		bCanBeDamaged = false;

		mpEnemyAIController->StopAI();
		GetWorld()->GetTimerManager().SetTimer(mDeadTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			Destroy();
			// enemy를 초기화 시킨다.
			//SetEnemyState(ECharacterState::LOADING);
			//mpSpawnActor->Spawn();
		}), mDeadTimer, false);
		break;
	}
	default:
		break;
	}
}

int32 AWEnemy::GetExp() const
{
	return CharacterStat->GetDropExp();
}

float AWEnemy::GetFinalAttackRange() const
{
	return (nullptr != mpCurrentWeapon) ? mpCurrentWeapon->GetAttackRange() : mAttackRange;
}

// Called every frame
void AWEnemy::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AWEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	mCharacterAnim = Cast<UWCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	WCHECK(nullptr != mCharacterAnim);

	mCharacterAnim->OnMontageEnded.AddDynamic(this, &AWEnemy::OnAttackMontageEnded);

	mCharacterAnim->OnAttackHitCheck.AddUObject(this, &AWEnemy::AttackCheck);
}

// Called to bind functionality to input
void AWEnemy::SetupPlayerInputComponent(UInputComponent* pPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(pPlayerInputComponent);
}

float AWEnemy::TakeDamage(float damage, FDamageEvent const & damageEvent, AController * eventInstigator, AActor * damageCauser)
{
	float finalDamage = Super::TakeDamage(damage, damageEvent, eventInstigator, damageCauser);
	//WLOG(Warning, TEXT("Enemy :  %s took Damage : %f"), *GetName(), finalDamage);

	CharacterStat->SetDamage(finalDamage);
	// 죽음
	if (mCurrentState == ECharacterState::DEAD)
	{
		auto playerController = Cast<AWPlayerController>(eventInstigator);
		WCHECK(nullptr != playerController, 0.0f);
		playerController->NPCKill(this);
	}
	return finalDamage;
}

void AWEnemy::SetWeapon(AWWeapon * pNewWeapon)
{
	WCHECK(nullptr != pNewWeapon);

	if (nullptr != mpCurrentWeapon)
	{
		mpCurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		mpCurrentWeapon->Destroy();
		mpCurrentWeapon = nullptr;
	}

	FName weaponSocket(TEXT("hand_rSocket"));
	if (nullptr != pNewWeapon)
	{
		pNewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocket);
		pNewWeapon->SetOwner(this);
		mpCurrentWeapon = pNewWeapon;
	}
}

void AWEnemy::Attack()
{
	mCharacterAnim->PlayAttackMontage();
}

void AWEnemy::OnAttackMontageEnded(UAnimMontage * pmontage, bool bInterrupted)
{
	OnAttackEnd.Broadcast();
}

// Called when the game starts or when spawned
void AWEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	mpEnemyAIController = Cast<AWEnemyAIController>(GetController());

	auto characterWidget = Cast<UWCharacterWidget>(mpHPBarWidget->GetUserWidgetObject());
	if (nullptr != characterWidget)
	{
		characterWidget->BindCharacterStat(CharacterStat);
	}

	// 메시 목록 외부에서 읽기
	auto defaultSetting = GetDefault<UWCharacterSetting>();
	int32 randomIndex = FMath::RandRange(0, defaultSetting->CharacterAssets.Num() - 1);
	mEnemyAssetToLoad = defaultSetting->CharacterAssets[randomIndex];

	auto gameInstance = Cast<UWGameInstance>(GetGameInstance());
	WCHECK(nullptr != gameInstance);
	mAssetStreamingHandle = gameInstance->StreamableManager.RequestAsyncLoad(
		mEnemyAssetToLoad, FStreamableDelegate::CreateUObject(this, &AWEnemy::OnAssetLoadCompleted));

	SetEnemyState(ECharacterState::LOADING);
}

void AWEnemy::OnAssetLoadCompleted()
{
	mAssetStreamingHandle->ReleaseHandle();
	TSoftObjectPtr<USkeletalMesh> loadedAssetPath(mEnemyAssetToLoad);
	WCHECK(loadedAssetPath.IsValid());

	GetMesh()->SetSkeletalMesh(loadedAssetPath.Get());
	SetEnemyState(ECharacterState::READY);
}

void AWEnemy::AttackCheck()
{
	float finalAttackRange = GetFinalAttackRange();
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * finalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		params);

#if ENABLE_DRAW_DEBUG

	FVector traceVec = GetActorForwardVector() * finalAttackRange;
	FVector center = GetActorLocation() + traceVec * 0.5f;
	float halfHeight = finalAttackRange * 0.5f + mAttackRadius;
	FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
	FColor drawColor = bResult ? FColor::Green : FColor::Red;
	float debugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		center,
		halfHeight,
		mAttackRadius,
		capsuleRot,
		drawColor,
		false,
		debugLifeTime);

#endif

	if (bResult)
	{
		if (hitResult.Actor.IsValid())
		{
			FDamageEvent damageEvent;
			hitResult.Actor->TakeDamage(CharacterStat->GetAttack(), damageEvent, GetController(), this);
		}
	}
}



