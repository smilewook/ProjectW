// Fill out your copyright notice in the Description page of Project Settings.


#include "WChestActor.h"
#include "ProjectWStructure.h"
#include "Items/WItemBase.h"
#include "Managers/WLootingManager.h"
#include "Player/WCharacter.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/WMainWidget.h"
#include "Widgets/Looting/WLootingWidget.h"
#include "Widgets/Misc/WPickupTextWidget.h"

#include <TextBlock.h>
#include <WidgetComponent.h>


AWChestActor::AWChestActor()
{
	PrimaryActorTick.bCanEverTick = false;

	mpSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = mpSceneComponent;

	mpTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("BoxTrigger"));
	mpTrigger->SetSphereRadius(100.f);
	mpTrigger->SetupAttachment(RootComponent);
	mpTrigger->SetCollisionProfileName(TEXT("WItemBox"));

	mpStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	mpStaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	mpStaticMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_DEFAULT(TEXT("/Game/Resources/Materials/M_DefaultPickup.M_DefaultPickup"));
	if (MAT_DEFAULT.Succeeded())
	{
		mpDefaultMaterial = MAT_DEFAULT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MAT_HOVERED(TEXT("/Game/Resources/Materials/M_HoveredPickup.M_HoveredPickup"));
	if (MAT_HOVERED.Succeeded())
	{
		mpHoveredMaterial = MAT_HOVERED.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_PICKUPTEXT(TEXT("/Game/Widgets/Misc/WB_PickupText.WB_PickupText_C"));
	if (WB_PICKUPTEXT.Succeeded())
	{
		mpPickupText = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupText"));
		mpPickupText->SetWidgetClass(WB_PICKUPTEXT.Class);
		mpPickupText->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		mpPickupText->SetWidgetSpace(EWidgetSpace::Screen);
		mpPickupText->SetDrawSize(FVector2D(150.f, 40.f));
		mpPickupText->SetVisibility(false);
		mpPickupText->SetupAttachment(mpStaticMesh);
	}

	mpLootingManager = CreateDefaultSubobject<UWLootingManager>(TEXT("LootingManager"));
}

void AWChestActor::UpdateText()
{
	UWPickupTextWidget* pPickupTextWidget = Cast<UWPickupTextWidget>(mpPickupText->GetUserWidgetObject());
	if (nullptr != pPickupTextWidget)
	{
		pPickupTextWidget->GetNameText()->SetText(FText::FromName(mName));
	}
}

void AWChestActor::OnPickedUp(AWPlayerCharacter* pPlayer)
{
	if (false == mpLootingManager->GetIsOpen())
	{
		UWLootingWidget* pLootingWidget = GetInteractionPlayer()->GetMainWidget()->GetLootingWidget();
		mpLootingManager->InitManager(pLootingWidget);
		mpLootingManager->Open();
	}
	if (nullptr != pPlayer)
	{
		// 적이 아이템을 드랍할 경우..
		if (mItemClasses.Num() > 0)
		{
			WLOG(Warning, TEXT("AWChestActor::OnPickedUp Open Looting.. : %s"), *GetName());
		}
		else
		{
			WLOG(Warning, TEXT("AWChestActor::OnPickedUp Failed."));
		}
	}
}

void AWChestActor::OnInteract(AWPlayerCharacter* pPlayer)
{
	// 현재 액터의 인터렉션 플레이어 설정.
	SetInteractionPlayer(pPlayer);
	GetInteractionPlayer()->SetTargetActor(this);
}

void AWChestActor::UnInteract()
{
	GetInteractionPlayer()->SetTargetActor(nullptr);
	SetInteractionPlayer(nullptr);

	if (true == mpLootingManager->GetIsOpen())
	{
		mpLootingManager->Close();
	}
}

void AWChestActor::AddItemClasses(const TArray<TSubclassOf<AWItemBase>>& itemClasses)
{
	for (auto itemClass : itemClasses)
	{
		mpLootingManager->AddItem(itemClass);
	}
}

void AWChestActor::BeginPlay()
{
	OnActivate();

	mpTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWChestActor::OnOverlapBegin);
	mpTrigger->OnComponentEndOverlap.AddDynamic(this, &AWChestActor::OnOverlapEnd);
}

void AWChestActor::OnActivate()
{
	UpdateText();
	mpPickupText->SetVisibility(true);
}

void AWChestActor::OnOverlapBegin(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(otherActor);
	WCHECK(::IsValid(pPlayer));
	if (::IsValid(pPlayer))
	{
		OnInteract(pPlayer);
		OnOvered();
	}
}

void AWChestActor::OnOverlapEnd(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex)
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(otherActor);
	WCHECK(::IsValid(pPlayer));
	if (::IsValid(pPlayer))
	{
		UnInteract();
		OnOuted();
	}
}

void AWChestActor::OnOvered()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Hand;
	mpStaticMesh->SetMaterial(0, mpHoveredMaterial);
}

void AWChestActor::OnOuted()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Default;
	mpStaticMesh->SetMaterial(0, mpOriginalMaterial);
}

