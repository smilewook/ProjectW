// Fill out your copyright notice in the Description page of Project Settings.


#include "WPickupActor.h"
#include "ProjectWStructure.h"
#include "Items/WItemBase.h"
#include "Managers/WInventoryManager.h"
#include "Player/WCharacter.h"
#include "Player/WPlayerCharacter.h"
#include "Widgets/Misc/WPickupTextWidget.h"

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

	mpStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	mpStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mpStaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
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

}

void AWPickupActor::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	
	// 아이템 속성에 접근해서 액터에 적용.
	if (nullptr != mItemClass)
	{
		FItemInfo ItemInfo = mItemClass.GetDefaultObject()->GetItemInfo();

		mpOriginalMaterial = mpStaticMesh->GetMaterial(0);

		mpStaticMesh->SetStaticMesh(ItemInfo.pStaticMesh);
		mpStaticMesh->SetRelativeScale3D(ItemInfo.MeshScale);

		mpTrigger->SetSphereRadius(ItemInfo.InteractRadius);
	}
}

void AWPickupActor::UpdateText()
{
	UWPickupTextWidget* pPickupTextWidget = Cast<UWPickupTextWidget>(mpPickupText->GetUserWidgetObject());
	if (nullptr != pPickupTextWidget)
	{
		FName itemName = mItemClass.GetDefaultObject()->GetItemInfo().Name;		
 		pPickupTextWidget->GetNameText()->SetText(FText::FromName(itemName));

		mName = itemName.ToString();
	}
}

void AWPickupActor::OnPickedUp(AWPlayerCharacter* pPlayer)
{
	if (nullptr != pPlayer)
	{
		// 인벤토리에 바로 넣기.
		bool bSuccess = pPlayer->GetInventoryManager()->AddItem(mItemClass, mAmount);
		if (true == bSuccess)
		{
			WLOG(Warning, TEXT("AWPickupActor::OnPickedUp Success!! : %s"), *GetName());

			Destroy();
		}
	}
}

void AWPickupActor::OnInteract(AWPlayerCharacter* pPlayer)
{
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
	GetInteractionPlayer()->DelTargetActor();
	mpInteractionPlayer = nullptr;
}

void AWPickupActor::BeginPlay()
{
	Super::BeginPlay();

	OnActivate();
	
	mpTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWPickupActor::OnOverlapBegin);
	mpTrigger->OnComponentEndOverlap.AddDynamic(this, &AWPickupActor::OnOverlapEnd);	
}

void AWPickupActor::OnActivate()
{
	UpdateText();
	mpPickupText->SetVisibility(true);
}

void AWPickupActor::OnOverlapBegin(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	//auto character = Cast<AWCharacter>(otherActor);
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(otherActor);
	WCHECK(::IsValid(pPlayer));
	if (::IsValid(pPlayer))
	{
		OnInteract(pPlayer);		
		mIsInRange = true;
	}
}

void AWPickupActor::OnOverlapEnd(UPrimitiveComponent * overlappedComp, AActor * otherActor, UPrimitiveComponent * otherComp, int32 otherBodyIndex)
{
	//auto character = Cast<AWCharacter>(otherActor);
	AWPlayerCharacter* pPlayer = Cast<AWPlayerCharacter>(otherActor);
	WCHECK(::IsValid(pPlayer));
	if (::IsValid(pPlayer))
	{
		UnInteract();
		mIsInRange = false;
	}
}

void AWPickupActor::OnHovered(UPrimitiveComponent* pTouchedComponent)
{
	mIsHovered = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Hand;
	mpStaticMesh->SetMaterial(0, mpHoveredMaterial);
	mpPickupText->SetVisibility(true);
}

void AWPickupActor::OnUnhovered(UPrimitiveComponent* pTouchedComponent)
{
	mIsHovered = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Default;
	mpStaticMesh->SetMaterial(0, mpOriginalMaterial);
	mpPickupText->SetVisibility(mIsInRange);
}
