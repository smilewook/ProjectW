// Fill out your copyright notice in the Description page of Project Settings.


#include "WWeapon.h"


AWWeapon::AWWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON_MESH(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Silly_Weapons/Blade_Baguette/SK_Blade_Baguette.SK_Blade_Baguette"));
	if (WEAPON_MESH.Succeeded())
	{
		Weapon->SetSkeletalMesh(WEAPON_MESH.Object);
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	mAttackRange = 150.0f;
	mAttackDamageMin = -2.5f;
	mAttackDamageMax = 10.0f;
	mAttackModifierMin = 0.85f;
	mAttackModifierMax = 1.25f;
}

float AWWeapon::GetAttackRange() const
{
	return mAttackRange;
}

float AWWeapon::GetAttackDamage() const
{
	return mAttackDamage;
}

float AWWeapon::GetAttackModifier() const
{
	return mAttackModifier;
}

void AWWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	mAttackDamage = FMath::RandRange(mAttackDamageMin, mAttackDamageMax);
	mAttackModifier = FMath::RandRange(mAttackModifierMin, mAttackModifierMax);
	WLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), mAttackDamage, mAttackModifier);
}



