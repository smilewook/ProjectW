// Fill out your copyright notice in the Description page of Project Settings.

#include "WCharacter.h"
#include "WCharacterAnimInstance.h"


// Sets default values
AWCharacter::AWCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mpSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	mpCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	mpSpringArm->SetupAttachment(GetCapsuleComponent());
	mpCamera->SetupAttachment(mpSpringArm);

	// 카메라 구도
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	mpSpringArm->TargetArmLength = 300.0f;
	mpSpringArm->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));

	// 스켈레탈 메시
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CHARACTER_MESH(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
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

	// 게임 화면 카메라 모드
	SetControlMode(EControlMode::DIABLO);

	// 카메라 이동 속도
	mArmLengthSpeed = 3.0f;
	// 카메라 회전 속도
	mArmRotationSpeed = 10.0f;
	// 점프 높이
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	// 공격 애니메이션 체크
	mIsAttacking = false;
	// 공격 콤보
	mMaxCombo = 2;
	AttackEndComboState();
}

// Called every frame
void AWCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	mpSpringArm->TargetArmLength = FMath::FInterpTo(mpSpringArm->TargetArmLength, mArmLengthTo, deltaTime, mArmLengthSpeed);

	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		break;
	case EControlMode::DIABLO:
		mpSpringArm->RelativeRotation = FMath::RInterpTo(mpSpringArm->RelativeRotation, mArmRotationTo, deltaTime, mArmRotationSpeed);
		if (mDirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(mDirectionToMove).Rotator());
			AddMovementInput(mDirectionToMove);
		}
		break;
	}
}

void AWCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	mCharacterAnim = Cast<UWCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	WCHECK(nullptr != mCharacterAnim);

	mCharacterAnim->OnMontageEnded.AddDynamic(this, &AWCharacter::OnAttackMontageEnded);

	mCharacterAnim->OnNextAttackCheck.AddLambda([this]() -> void {
		mCanNextCombo = false;
		if (mIsComboInputOn)
		{
			AttackStartComboState();
			mCharacterAnim->JumpToAttackMontageSection(mCurrentCombo);
		}
	});
}

// Called to bind functionality to input
void AWCharacter::SetupPlayerInputComponent(UInputComponent* pPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(pPlayerInputComponent);

	pPlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AWCharacter::ViewChange);
	pPlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AWCharacter::Jump);
	pPlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AWCharacter::Attack);

	pPlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWCharacter::MoveForward);
	pPlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AWCharacter::MoveRight);
	pPlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AWCharacter::LookUp);
	pPlayerInputComponent->BindAxis(TEXT("Turn"), this, &AWCharacter::Turn);
}

// Called when the game starts or when spawned
void AWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWCharacter::SetControlMode(EControlMode controlMode)
{
	mCurrentControlMode = controlMode;

	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		mArmLengthTo = 500.0f;
		mpSpringArm->bUsePawnControlRotation = true;
		mpSpringArm->bInheritPitch = true;
		mpSpringArm->bInheritRoll = true;
		mpSpringArm->bInheritYaw = true;
		mpSpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		mArmLengthTo = 900.0f;
		mArmRotationTo = FRotator(-50.0f, 0.0f, 0.0f);
		mpSpringArm->bUsePawnControlRotation = false;
		mpSpringArm->bInheritPitch = false;
		mpSpringArm->bInheritRoll = false;
		mpSpringArm->bInheritYaw = false;
		mpSpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	default:
		break;
	}
}

void AWCharacter::MoveForward(float newAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), newAxisValue);
		break;
	case EControlMode::DIABLO:
		mDirectionToMove.X = newAxisValue;
		break;
	}
}

void AWCharacter::MoveRight(float newAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), newAxisValue);
		break;
	case EControlMode::DIABLO:
		mDirectionToMove.Y = newAxisValue;
		break;
	}
}

void AWCharacter::LookUp(float newAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(newAxisValue);
		break;
	case EControlMode::DIABLO:
		break;
	}
}

void AWCharacter::Turn(float newAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(newAxisValue);
		break;
	case EControlMode::DIABLO:
		break;
	}
}

void AWCharacter::ViewChange()
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(mpSpringArm->RelativeRotation);
		SetControlMode(EControlMode::GTA);
		break;
	}
}

void AWCharacter::Attack()
{
	if (mIsAttacking)
	{
		
		WCHECK(FMath::IsWithinInclusive<int32>(mCurrentCombo, 1, mMaxCombo));
		if (mCanNextCombo)
		{
			mIsComboInputOn = true;
		}
	}
	else
	{
		WCHECK(mCurrentCombo == 0);
		AttackStartComboState();
		mCharacterAnim->PlayAttackMontage();
		mCharacterAnim->JumpToAttackMontageSection(mCurrentCombo);
		mIsAttacking = true;
	}
}

void AWCharacter::OnAttackMontageEnded(UAnimMontage * pmontage, bool bInterrupted)
{
	WCHECK(mIsAttacking);
	WCHECK(mCurrentCombo > 0);
	mIsAttacking = false;
	AttackEndComboState();
}

void AWCharacter::AttackStartComboState()
{
	mCanNextCombo = true;
	mIsComboInputOn = false;
	WCHECK(FMath::IsWithinInclusive<int32>(mCurrentCombo, 0, mMaxCombo - 1));
	mCurrentCombo = FMath::Clamp<int32>(mCurrentCombo + 1, 1, mMaxCombo);
}

void AWCharacter::AttackEndComboState()
{
	WLOG(Warning, TEXT("AttackEndComboState"));
	mIsComboInputOn = false;
	mCanNextCombo = false;
	mCurrentCombo = 0;
}

