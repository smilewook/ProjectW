// Fill out your copyright notice in the Description page of Project Settings.


#include "WPlayerCharacter.h"
#include "WPlayerController.h"
#include "Actors/WPickupActor.h"
#include "Items/WItemEquipment.h"
#include "Managers/WEquipmentManager.h"
#include "Managers/WInventoryManager.h"
#include "Managers/WStatManager.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/Equipment/WEquipmentWidget.h"
#include "Widgets/Inventory/WInventoryWidget.h"
#include "Widgets/Stat/WStatWidget.h"

#include <WidgetBlueprintLibrary.h>


AWPlayerCharacter::AWPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	mpSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mpCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mpSpringArm->SetupAttachment(GetCapsuleComponent());
	mpCamera->SetupAttachment(mpSpringArm);

	// 카메라 구도.
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
	// 점프 높이.
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	// 이동 속도.
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	// 스켈레탈 메시.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CHARACTER_MESH(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (CHARACTER_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CHARACTER_MESH.Object);
	}

	// 애니메이션 인스턴스.
	static ConstructorHelpers::FClassFinder<UAnimInstance> CHARACTER_ANIM(TEXT("/Game/Animations/CharacterAnimBP.CharacterAnimBP_C"));
	if (CHARACTER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CHARACTER_ANIM.Class);
	}
	
	// 캐릭터 콜리전.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("WCharacter"));

	// 컨텐츠 생성.	
	mpInventoryManager = CreateDefaultSubobject<UWInventoryManager>(TEXT("Inventory"));
	mpStatManager = CreateDefaultSubobject<UWStatManager>(TEXT("Stat"));
	mpEquipmentManager = CreateDefaultSubobject<UWEquipmentManager>(TEXT("Equipment"));
	
	// 장착 장비.
 	mpWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
 	mpWeaponMesh->SetupAttachment(GetMesh());
	mpSecondWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SecondWeaponMesh"));
	mpSecondWeaponMesh->SetupAttachment(GetMesh());
}

void AWPlayerCharacter::DelTargetActor()
{
	if (nullptr != mpTargetActor)
	{
		mpTargetActor = nullptr;
	}
}

void AWPlayerCharacter::SetWeapon(AWItemEquipment* pNewWeapon)
{
	if (nullptr != mpCurrentWeapon)
	{
		mpWeaponMesh->SetSkeletalMesh(nullptr);
		mpCurrentWeapon->Destroy();
		mpCurrentWeapon = nullptr;
	}

	if (nullptr != pNewWeapon)
	{
		mpCurrentWeapon = pNewWeapon;

		mpWeaponMesh->SetSkeletalMesh(mpCurrentWeapon->GetWeaponMesh());
		mpWeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, mpCurrentWeapon->GetSocketName());
	}
}

void AWPlayerCharacter::SetSecondWeapon(AWItemEquipment* pNewWeapon)
{
	if (nullptr != mpCurrentSecondWeapon)
	{
		mpSecondWeaponMesh->SetSkeletalMesh(nullptr);
		mpCurrentSecondWeapon->Destroy();
		mpCurrentSecondWeapon = nullptr;
	}

	if (nullptr != pNewWeapon)
	{
		mpCurrentSecondWeapon = pNewWeapon;

		mpSecondWeaponMesh->SetSkeletalMesh(mpCurrentSecondWeapon->GetWeaponMesh());
		mpSecondWeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, mpCurrentSecondWeapon->GetSocketName());
	}
}

bool AWPlayerCharacter::ModifyStatAttribute(EStatAttributeType statType, float value)
{
	return mpStatManager->ModifyStatAttribute(statType, value);
}

void AWPlayerCharacter::Interact()
{
	if (nullptr != GetTargetActor())
	{
		WLOG(Warning, TEXT("TargetActor is real!"));
		mpTargetActor->OnPickedUp(this);
	}
	else
	{
		WLOG(Warning, TEXT("TargetActor is null!"));
	}
}

void AWPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	mpPlayerController = Cast<AWPlayerController>(GetController());
	WCHECK(nullptr != mpPlayerController);
	mpMainWidget = mpPlayerController->GetMainWidget();

	// 메인 위젯 초기화 확인.
	bool bInitialize = mpMainWidget->InitWidget(this);
	if (true == bInitialize)
	{
		// 각 컨텐츠에 위젯 등록.
		mpInventoryManager->InitManager(mpMainWidget->GetInventoryWidget());
		mpStatManager->InitManager(mpMainWidget->GetStatWidget());
		mpEquipmentManager->InitManager(mpMainWidget->GetEquipmentWidget());
	}
	else
	{
		WLOG(Warning, TEXT("Create MainWidget Failed."));
	}
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
	pPlayerInputComponent->BindAction(TEXT("ToggleMouseCursor"), EInputEvent::IE_Pressed, this, &AWPlayerCharacter::ToggleMouseCursor);
	pPlayerInputComponent->BindAction(TEXT("ToggleInventory"), EInputEvent::IE_Pressed, this, &AWPlayerCharacter::ToggleInventory);
	pPlayerInputComponent->BindAction(TEXT("ToggleStat"), EInputEvent::IE_Pressed, this, &AWPlayerCharacter::ToggleStat);
	pPlayerInputComponent->BindAction(TEXT("ToggleEquip"), EInputEvent::IE_Pressed, this, &AWPlayerCharacter::ToggleEquip);

	pPlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWPlayerCharacter::MoveForward);
	pPlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AWPlayerCharacter::MoveRight);
	pPlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AWPlayerCharacter::LookUp);
	pPlayerInputComponent->BindAxis(TEXT("Turn"), this, &AWPlayerCharacter::Turn);
}

void AWPlayerCharacter::ToggleMouseCursor()
{
	mpPlayerController->bShowMouseCursor = !mpPlayerController->bShowMouseCursor;
	if (mpPlayerController->bShowMouseCursor)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(mpPlayerController);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(mpPlayerController);
	}
}

void AWPlayerCharacter::ToggleInventory()
{
	if (nullptr != mpInventoryManager)
	{
		if (mpInventoryManager->GetIsOpen())
		{
			mpInventoryManager->Close();
		}
		else
		{
			mpInventoryManager->Open();
		}
	}
}

void AWPlayerCharacter::ToggleStat()
{
	if (nullptr != mpStatManager)
	{
		if (mpStatManager->GetIsOpen())
		{
			mpStatManager->Close();
		}
		else
		{
			mpStatManager->Open();
		}
	}
}

void AWPlayerCharacter::ToggleEquip()
{
	if (nullptr != mpEquipmentManager)
	{
		if (mpEquipmentManager->GetIsOpen())
		{
			mpEquipmentManager->Close();
		}
		else
		{
			mpEquipmentManager->Open();
		}
	}
}

void AWPlayerCharacter::MoveForward(float newAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), newAxisValue);
}

void AWPlayerCharacter::MoveRight(float newAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), newAxisValue);
}

void AWPlayerCharacter::LookUp(float newAxisValue)
{
	AddControllerPitchInput(newAxisValue);
}

void AWPlayerCharacter::Turn(float newAxisValue)
{
	AddControllerYawInput(newAxisValue);
}


