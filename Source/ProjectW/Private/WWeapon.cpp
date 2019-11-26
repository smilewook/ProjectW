// Fill out your copyright notice in the Description page of Project Settings.


#include "WWeapon.h"

// Sets default values
AWWeapon::AWWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WEAPON_MESH(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Silly_Weapons/Blade_Baguette/SK_Blade_Baguette.SK_Blade_Baguette"));
	if (WEAPON_MESH.Succeeded())
	{
		Weapon->SetSkeletalMesh(WEAPON_MESH.Object);
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called every frame
void AWWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AWWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}



