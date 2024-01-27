// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "BuildingUI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UBuildingUI : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building UI", meta = (BindWidget))
	class UButton* btnUpgrade;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building UI", meta = (BindWidget))
	class UButton* btnMove;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building UI", meta = (BindWidget))
	class UButton* btnDestroy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private", meta = (ExposeOnSpawn = true))
	AInputController* InputController;
	
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpgrade();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnMove();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDestroy();

};
