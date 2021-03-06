// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/NInteractableInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "NPickupActor.generated.h"

class UCapsuleComponent;
class UNItem;

UCLASS()
class NETWORKEDRPG_API ANPickupActor : public AActor, public INInteractableInterface
{
	GENERATED_BODY()

public:
	/** Sets default values for this actor's properties */
	ANPickupActor();

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 1. Blueprint Settings
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:	
	/** The item data class to pickup */
	UPROPERTY(ReplicatedUsing=OnRep_Item, EditAnywhere, BlueprintReadWrite, Category = "Item|Data")
	UNItem* ItemData;

	/** The number of items to add when this is picked up */
	UPROPERTY(EditAnywhere, Category = "Item|Data")
	int32 ItemCount;

	/** The level of the item to pickup */
	UPROPERTY(EditAnywhere, Category = "Item|Data")
	int32 ItemLevel;
	
	/** Will use item mesh attached to the Item data if true, else use the Mesh below */
	UPROPERTY(EditAnywhere, Category="Item|Mesh")
	bool bUseItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Mesh", meta = (EditCondition = "!bUseItemMesh"))
	USkeletalMeshComponent* SkeletalMesh;

	/** The curve for the bobbing animation, should start and end with a value of 0 */
	UPROPERTY(EditAnywhere, Category = "Item|Animation")
	UCurveFloat* BobbingCurve;

	/** The max height of the bobbing animation */
	UPROPERTY(EditAnywhere, Category = "Item|Animation")
	float BobbingHeight;

	/** The rotation speed for the animation */
	UPROPERTY(EditAnywhere, Category = "Item|Animation")
	FRotator RotationSpeed;

	/** The offset of the interaction indicator from the root component */
	UPROPERTY(EditAnywhere, Category = "Item|Interaction")
	FVector InteractionIndicatorOffset;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 2. Components
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** The physics collision capsule that interacts with */
	UPROPERTY(EditAnywhere, Category = "Item")
	UCapsuleComponent* CollisionCapsule;

	/** The sphere in which the item is detected */
	UPROPERTY(EditAnywhere, Category = "Item")
	UCapsuleComponent* PickupCapsuleComponent;

	/** The "Root" of the component. */
	UPROPERTY(VisibleAnywhere, Category="Item")
	USceneComponent* AnimationRoot;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 3. References and State
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	FTimeline BobbingTimeline;
	FVector InitialOffset;
	FTimerHandle TimerHandle;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 4. Overrides
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	/** Called every frame if BobbingCurve and BobbingHeight or RotationSpeed are set */
	virtual void Tick(float DeltaTime) override;

	/** Updates the mesh to the Item mesh if bUseItemMesh is true */
	virtual void OnConstruction(const FTransform& Transform) override;

	/** Replicates ItemData. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** NInteractableInterface */
	virtual void Interact(AActor*InActor) override;
	virtual FVector GetIndicatorOffset() override;
	virtual USceneComponent* GetInteractableRootComponent() override;
	virtual ENInteractableType GetInteractableType() override;
	
protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 5. Interface and Methods
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	/** Sets the item and count and updates the mesh */
	void SetItem(UNItem* InItem, int32 InCount);

private:
	/** Updates the item mesh to that of the Item data */
	void UpdateItemMesh() const;
	
	UFUNCTION()
	void HandleTimelineAnimation(float Value);

	/** Updates the item mesh */
	UFUNCTION()
	void OnRep_Item() const;

};
