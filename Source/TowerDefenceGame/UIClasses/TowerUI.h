// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/Actors/PlacementActor.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerUI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UTowerUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnConfirmPlacement;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnAbortPlacement;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnConfirmPlacement();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAbortPlacement();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlacementStateUpdate(EPlacementState State, APlacementActor* PlacementActor);
};
