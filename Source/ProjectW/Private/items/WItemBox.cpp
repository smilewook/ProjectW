// Fill out your copyright notice in the Description page of Project Settings.


#include "WItemBox.h"
#include "WWeapon.h"
#include "WCharacter.h"


// Sets default values
AWItemBox::AWItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PARTICLE_BOX_OPEN(TEXT("/Game/InfinityBladeEffects/Effects/FX_Skill_Leap/P_Skill_Leap_Base_Charge_Weapon.P_Skill_Leap_Base_Charge_Weapon"));
	if (PARTICLE_BOX_OPEN.Succeeded())
	{
		Effect->SetTemplate(PARTICLE_BOX_OPEN.Object);
		Effect->bAutoActivate = false;
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("WItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	
	WeaponItemClass = AWWeapon::StaticClass();
}

// Called every frame
void AWItemBox::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

// Called when the game starts or when spawned
void AWItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWItemBox::OnCharacterOverlap);
}

void AWItemBox::OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	//WLOG_S(Warning);

	auto character = Cast<AWCharacter>(otherActor);
	WCHECK(nullptr != character);

	if (nullptr != character && nullptr != WeaponItemClass)
	{
		if (character->CanSetWeapon())
		{
			auto newWeapon = GetWorld()->SpawnActor<AWWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			character->SetWeapon(newWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &AWItemBox::OnEffectFinished);
		}
		else
		{
			WLOG(Warning, TEXT("%s cant equip weapon."), *character->GetName());
		}
	}
}

void AWItemBox::OnEffectFinished(class UParticleSystemComponent* pParticleSystem)
{
	Destroy();
}

