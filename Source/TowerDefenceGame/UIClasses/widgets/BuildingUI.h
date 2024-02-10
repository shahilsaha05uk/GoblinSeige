// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "BuildingUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeSignature);
UCLASS()
class TOWERDEFENCEGAME_API UBuildingUI : public UBaseWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
	class ABaseBuilding* mParentBuilding;
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building UI", meta = (BindWidget))
	class UButton* btnUpgrade;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building UI", meta = (BindWidget))
	class UButton* btnMove;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building UI", meta = (BindWidget))
	class UButton* btnDestroy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private", meta = (ExposeOnSpawn = true))
	AInputController* InputController;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnUpgradeSignature OnUpgradeSignature;

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitialiseWidget(class ABaseBuilding* ParentBuilding);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpgrade();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnMove();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDestroy();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnFullyUpgraded();
};
