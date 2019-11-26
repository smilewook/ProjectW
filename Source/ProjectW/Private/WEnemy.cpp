// Fill out your copyright notice in the Description page of Project Settings.


#include "WEnemy.h"
#include "WCharacterAnimInstance.h"
#include "WCharacterStatComponent.h"
#include "WWeapon.h"
#include "WCharacterWidget.h"
#include "WEnemyAIController.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"


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

	// 공격 애니메이션 체크
	mIsAttacking = false;
	// 콜리전 프리셋
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("WCharacter"));
	// 공격 범위 디버깅
	mAttackRange = 200.0f;
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

	mCharacterAnim->OnAttackHitCheck.AddUObject(this, &AWEnemy::AttackCheck);

	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		mCharacterAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	});

}

// Called to bind functionality to input
void AWEnemy::SetupPlayerInputComponent(UInputComponent* pPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(pPlayerInputComponent);
}

float AWEnemy::TakeDamage(float damage, FDamageEvent const & damageEvent, AController * eventInstigator, AActor * damageCauser)
{
	float finalDamage = Super::TakeDamage(damage, damageEvent, eventInstigator, damageCauser);
	WLOG(Warning, TEXT("Enemy :  %s took Damage : %f"), *GetName(), finalDamage);

	CharacterStat->SetDamage(finalDamage);
	return finalDamage;
}

void AWEnemy::SetWeapon(AWWeapon * pNewWeapon)
{
	WCHECK(nullptr != pNewWeapon && nullptr == mpCurrentWeapon);
	FName weaponSocket(TEXT("hand_rSocket"));
	if (nullptr != pNewWeapon)
	{
		pNewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weaponSocket);
		pNewWeapon->SetOwner(this);
		mpCurrentWeapon = pNewWeapon;
	}
}

// Called when the game starts or when spawned
void AWEnemy::BeginPlay()
{
	Super::BeginPlay();

	auto characterWidget = Cast<UWCharacterWidget>(mpHPBarWidget->GetUserWidgetObject());
	if (nullptr != characterWidget)
	{
		characterWidget->BindCharacterStat(CharacterStat);
	}
}

void AWEnemy::AttackCheck()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * mAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		params);

#if ENABLE_DRAW_DEBUG

	FVector traceVec = GetActorForwardVector() * mAttackRange;
	FVector center = GetActorLocation() + traceVec * 0.5f;
	float halfHeight = mAttackRange * 0.5f + mAttackRadius;
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



