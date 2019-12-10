// Fill out your copyright notice in the Description page of Project Settings.


#include "WPickupActor.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"
#include "Player/WCharacter.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/WPickupTextWidget.h"

#include <TextBlock.h>
#include <WidgetComponent.h>


AWPickupActor::AWPickupActor()
{
 	PrimaryActorTick.bCanEverTick = false;

	mpSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = mpSceneComponent;

	mpTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("BoxTrigger"));
	mpTrigger->SetSphereRadius(100.f);
	mpTrigger->SetupAttachment(RootComponent);
	mpTrigger->SetCollisionProfileName(TEXT("WItemBox"));

	mpItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	mpItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mpItemMesh->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	mpItemMesh->SetupAttachment(RootComponent);

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

	static ConstructorHelpers::FClassFinder<UUserWidget> WB_PICKUPTEXT(TEXT("/Game/Widgets/WB_PickupText.WB_PickupText_C"));
	if (WB_PICKUPTEXT.Succeeded())
	{
		mpPickupText = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupText"));
		mpPickupText->SetWidgetClass(WB_PICKUPTEXT.Class);
		mpPickupText->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
		mpPickupText->SetWidgetSpace(EWidgetSpace::Screen);
		mpPickupText->SetDrawSize(FVector2D(100.f, 100.f));
		mpPickupText->SetVisibility(false);
		mpPickupText->SetupAttachment(mpItemMesh);
	}

}

void AWPickupActor::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	if (nullptr != mItemClass)
	{
// 		FItemInfo ItemInfo = mItemClass.GetDefaultObject()->GetItemInfo();
// 
//		mpOriginalMaterial = mpItemMesh->GetMaterial(0);
//
// 		mpItemMesh->SetStaticMesh(ItemInfo.pStaticMesh);
// 		mpItemMesh->SetRelativeScale3D(ItemInfo.MeshScale);
// 
// 		mpTrigger->SetSphereRadius(ItemInfo.InteractRadius);
	}
}

void AWPickupActor::UpdateText()
{
	UWPickupTextWidget* pPickupTextWidget = Cast<UWPickupTextWidget>(mpPickupText->GetUserWidgetObject());
	if (nullptr != pPickupTextWidget)
	{
		FName itemName = FName(TEXT("ItemName"));
		FText text = FText::FromName(itemName);
// 		FName ItemName = mItemClass.GetDefaultObject()->GetItemInfo().Name;
// 		FText text = FText::Format(LOCTEXT("Format", "{0} ({1})"), FText::FromName(ItemName), m_Amount);
 		pPickupTextWidget->GetNameText()->SetText(text);
	}
}

void AWPickupActor::OnPickedUp(AActor* pActor)
{
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(pActor);
	if (nullptr != pPlayer)
	{
		//pPlayer->GetInventory()->AddItem();

		FString pickup = FString::Printf(TEXT("Picked up : %s"), *GetName());
		GEngine->AddOnScreenDebugMessage(1, 4, FColor::White, pickup);
		Destroy();
	}
}

void AWPickupActor::OnInteract(AWPlayerCharacter* pPlayer)
{
	WLOG(Warning, TEXT("OnInteract PickupActor!!"));
	// 현재 액터의 인터렉션 플레이어 설정.
	SetInteractionPlayer(pPlayer);	
	GetInteractionPlayer()->SetTargetActor(this);
	
	// 루팅 위젯이 있으면 세팅 후 오픈.
	//UWidget_Base* pWidget = GetInteractionUser()->GetMainWidget()->GetPickupWidget();
	//mpPickup->InitComponent(pWidget);
	//mpPickup->Open();
	
}

void AWPickupActor::UnInteract()
{
	WLOG(Warning, TEXT("UnInteract PickupActor!!"));
	GetInteractionPlayer()->DelTargetActor();
	mpInteractionPlayer = nullptr;
}

void AWPickupActor::BeginPlay()
{
	Super::BeginPlay();
	
	mpTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWPickupActor::OnOverlapBegin);
	mpTrigger->OnComponentEndOverlap.AddDynamic(this, &AWPickupActor::OnOverlapEnd);
}

void AWPickupActor::OnOverlapBegin(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	//auto character = Cast<AWCharacter>(otherActor);
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(otherActor);
	WCHECK(nullptr != pPlayer);

	if (nullptr != pPlayer)
	{
		OnInteract(pPlayer);

		mpPickupText->SetVisibility(true);
	}
}

void AWPickupActor::OnOverlapEnd(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex)
{
	//auto character = Cast<AWCharacter>(otherActor);
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(otherActor);
	WCHECK(nullptr != pPlayer);

	if (nullptr != pPlayer)
	{
		UnInteract();

		mIsInRange = false;
		mpPickupText->SetVisibility(false);
	}
}

void AWPickupActor::OnHovered(UPrimitiveComponent* pTouchedComponent)
{
	mIsHovered = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Hand;
	mpItemMesh->SetMaterial(0, mpHoveredMaterial);
	mpPickupText->SetVisibility(true);
}

void AWPickupActor::OnUnhovered(UPrimitiveComponent* pTouchedComponent)
{
	mIsHovered = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Default;
	mpItemMesh->SetMaterial(0, mpOriginalMaterial);
	mpPickupText->SetVisibility(mIsInRange);
}
