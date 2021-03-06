// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NPlayerController.generated.h"

class UNHUDWidget;
class UNInventoryComponent;
class UNInventoryWidget;

/**
 * Player controller class that holds a UNInventoryComponent;
 */
UCLASS()
class NETWORKEDRPG_API ANPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANPlayerController();

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 1. Blueprint Settings
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UNHUDWidget> UIHUDWidgetClass;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 2. Components
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	/** Hold our inventory component here so it stays persistent */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|CombatComponent")
	UNInventoryComponent* InventoryComponent;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 3. References
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	UNHUDWidget* UIHUDWidget;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 4. Overrides
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 5. Interface and Methods
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	void CreateHUD();
	
	UNHUDWidget* GetHUDWidget() const;

};
