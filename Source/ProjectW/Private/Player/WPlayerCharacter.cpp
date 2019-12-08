// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerCharacter.h"
#include "WInventoryManager.h"
#include "WPickupActor.h"


AWPlayerCharacter::AWPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	mpSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mpCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mpSpringArm->SetupAttachment(GetCapsuleComponent());
	mpCamera->SetupAttachment(mpSpringArm);

	// ī�޶� ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	mpSpringArm->TargetArmLength = 600.0f;
	mpSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	mpSpringArm->bUsePawnControlRotation = true;
	mpSpringArm->bInheritPitch = true;
	mpSpringArm->bInheritRoll = true;
	mpSpringArm->bInheritYaw = true;
	mpSpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	// ���� ����
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	// �̵� �ӵ�
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	// ���̷�Ż �޽�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CHARACTER_MESH(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (CHARACTER_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CHARACTER_MESH.Object);
	}

	// �ִϸ��̼� �ν��Ͻ�
	static ConstructorHelpers::FClassFinder<UAnimInstance> CHARACTER_ANIM(TEXT("/Game/Animations/CharacterAnimBP.CharacterAnimBP_C"));
	if (CHARACTER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CHARACTER_ANIM.Class);
	}
	
	// ĳ���� �ݸ���
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("WCharacter"));

	// ������
	mpInventory = CreateDefaultSubobject<UWInventoryManager>(TEXT("Inventory"));
}

void AWPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWPlayerCharacter::SetupPlayerInputComponent(UInputComponent* pPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(pPlayerInputComponent);

	pPlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AWPlayerCharacter::Jump);
	pPlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AWPlayerCharacter::Interact);

	pPlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWPlayerCharacter::MoveForward);
	pPlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AWPlayerCharacter::MoveRight);
	pPlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AWPlayerCharacter::LookUp);
	pPlayerInputComponent->BindAxis(TEXT("Turn"), this, &AWPlayerCharacter::Turn);
}

void AWPlayerCharacter::DelTargetActor()
{
	mpTargetActor = nullptr;
}

void AWPlayerCharacter::Interact()
{
	if (nullptr != GetTargetActor())
	{
		WLOG(Warning, TEXT("TargetActor is real!"));
	}
	else
	{
		WLOG(Warning, TEXT("TargetActor is null!"));
	}
	FHitResult hitResult;
	FVector direction = mpCamera->GetForwardVector();
	FVector startLoc = mpCamera->GetComponentLocation();
	FVector endLoc = startLoc + (direction * 1000.0f);

// 	FCollisionObjectQueryParams CollisionObjectQueryParams;
// 	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_EngineTraceChannel2);
// 	FCollisionQueryParams CollisionQueryParams(FName(""), false, GetOwner()
	
// 	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_Visibility))
// 	{
// 		// ��ȣ�ۿ��� ������ ������ ���.
// 		if (IInterface_Interaction* pInteract = Cast<IInterface_Interaction>(Result.GetActor()))
// 		{
// 			pInteract->GetInteractionUser() ? pInteract->UnInteract() : pInteract->OnInteract(m_pPlayer);
// 			return;
// 		}
// 	}
// 
// 	if (GetTarget())
// 	{
// 		IInterface_Interaction* pInteract = Cast<IInterface_Interaction>(m_pPlayer->GetTarget());
// 		pInteract->UnInteract();
// 		return;
// 	}
}

void AWPlayerCharacter::MoveForward(float newAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), newAxisValue);
	//AddMovementInput(GetActorForwardVector(), newAxisValue);
}

void AWPlayerCharacter::MoveRight(float newAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), newAxisValue);
	//AddMovementInput(GetActorRightVector(), newAxisValue);
}

void AWPlayerCharacter::LookUp(float newAxisValue)
{
	AddControllerPitchInput(newAxisValue);
}

void AWPlayerCharacter::Turn(float newAxisValue)
{
	AddControllerYawInput(newAxisValue);
}


