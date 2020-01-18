// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectW.h"
#include "GameFramework/Actor.h"
#include "WChestActor.generated.h"


class AWItemBase;
class AWPlayerCharacter;

class UMaterial;
class UWidgetComponent;
class UWLootingManager;


UCLASS()
class PROJECTW_API AWChestActor : public AActor
{
	GENERATED_BODY()
	
	/* Methods */
public:	
	AWChestActor();

	void UpdateText();
	void OnPickedUp(AWPlayerCharacter* pPlayer);
	void OnInteract(AWPlayerCharacter* pPlayer);
	void UnInteract();
	void AddItemClasses(const TArray<TSubclassOf<AWItemBase>>& itemClasses);

	/* Get/Set */
	FORCEINLINE USphereComponent*	const& GetSphere()				const { return mpTrigger; }
	FORCEINLINE UWidgetComponent*	const& GetPickupText()			const { return mpPickupText; }
	FORCEINLINE AWPlayerCharacter*	const& GetInteractionPlayer()	const { return mpInteractionPlayer; }

	FORCEINLINE void SetInteractionPlayer(AWPlayerCharacter* pPlayer) { WCHECK(nullptr != pPlayer); mpInteractionPlayer = pPlayer; }

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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UWLootingManager* mpLootingManager;

	UPROPERTY(EditAnywhere, Category = "Configuration | Material")
	UStaticMeshComponent* mpStaticMesh;	

	UPROPERTY(EditAnywhere, Category = "Configuration | Material")
	UMaterial* mpDefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Configuration | Material")
	UMaterial* mpHoveredMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration | Data")
	TArray<TSubclassOf<AWItemBase>> mItemClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration | Data")
	FName mName;

	UMaterialInterface* mpOriginalMaterial;

	AWPlayerCharacter* mpInteractionPlayer;

};
