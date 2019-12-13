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
	FORCEINLINE USphereComponent* const& GetSphere() const { return mpTrigger; }
	FORCEINLINE const FString& GetName() const { return mName; }
	FORCEINLINE const int& GetID() const { return mID; }
	FORCEINLINE const int& GetAmount() const { return mAmount; }
	FORCEINLINE UWidgetComponent* const& GetPickupText() const { return mpPickupText; }
	FORCEINLINE AWPlayerCharacter* const& GetInteractionPlayer() const { return mpInteractionPlayer; }

	/* Set */
	FORCEINLINE void SetAmount(int amount) { mAmount = amount; }
	FORCEINLINE void SetHasPickupCommand(bool hasCommand) { mHasPickupCommand = hasCommand; }
	FORCEINLINE void SetInteractionPlayer(class AWPlayerCharacter* pPlayer) { mpInteractionPlayer = pPlayer; WCHECK(nullptr != mpInteractionPlayer); }

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
	void OnHovered(UPrimitiveComponent* pTouchedComponent);

	UFUNCTION()
	void OnUnhovered(UPrimitiveComponent* pTouchedComponent);

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
	FString mName;

	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	int32 mID;

	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	TSubclassOf<AWItemBase> mItemClass;

	UPROPERTY(EditAnywhere, Category = "Configuration | Data")
	int32 mAmount;

	bool mIsHovered;
	bool mIsInRange;
	bool mHasPickupCommand;

	UMaterialInterface* mpOriginalMaterial;

	AWPlayerCharacter* mpInteractionPlayer;

};
