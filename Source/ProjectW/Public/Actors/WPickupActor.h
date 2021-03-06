// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Actor.h"
#include "WPickupActor.generated.h"


class AWItemBase;
class AWPlayerCharacter;

class UMaterial;
class UWidgetComponent;


UCLASS()
class PROJECTW_API AWPickupActor : public AActor
{
	GENERATED_BODY()
	
	/* Methods */
public:
	AWPickupActor();

	virtual void OnConstruction(const FTransform& transform) override;

	void UpdateText();
	void OnPickedUp(AWPlayerCharacter* pPlayer);
	void OnInteract(AWPlayerCharacter* pPlayer);
	void UnInteract();

	/* Get/Set */
	FORCEINLINE AWPlayerCharacter* const& GetInteractionPlayer() const { return mpInteractionPlayer; }

	FORCEINLINE void SetInteractionPlayer(AWPlayerCharacter* pPlayer) { WCHECK(nullptr != pPlayer); mpInteractionPlayer = pPlayer;  }

protected:
	virtual void BeginPlay() override;

	void OnActivate();

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);

	// 아이템 마우스 오버아웃
	UFUNCTION()
	void OnOvered(/*UPrimitiveComponent* pTouchedComponent*/);

	UFUNCTION()
	void OnOuted(/*UPrimitiveComponent* pTouchedComponent*/);

	/* Properties */
protected:
	UPROPERTY()
	USceneComponent* mpSceneComponent;

	UPROPERTY()
	USphereComponent* mpTrigger;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* mpPickupText;
	
	UPROPERTY(VisibleAnywhere, Category = "Configuration | Material")
	UStaticMeshComponent* mpStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Configuration | Material")
	UMaterial* mpDefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Configuration | Material")
	UMaterial* mpHoveredMaterial;	

	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	int32 mID;

	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	TSubclassOf<AWItemBase> mItemClass;

	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	int32 mAmount;

	UMaterialInterface* mpOriginalMaterial;

	AWPlayerCharacter* mpInteractionPlayer;

private:
	
};
