// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "DescriptionBox.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UDescriptionBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDA_BuildingAsset* mBuildingAsset;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtBuildingName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtCost;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UDescriptionEntry* entryDamage;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UDescriptionEntry* entryRange;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UDescriptionEntry* entryRateOfFire;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ModifyForUpgrade(class ABaseBuilding* BuildingRef);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ModifyForBuy(FBuildingBuyDetails BuildingDetails);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ModifyWhenUnHovered();
	
	UFUNCTION(BlueprintCallable)
	void ClearFields();
	UFUNCTION(BlueprintCallable)
	void UpgradeCurrents(FBuildingStats Stats);
	UFUNCTION(BlueprintCallable)
	void UpgradeNexts(FBuildingStats CurrentStats, FBuildingStats NextStats);
	UFUNCTION(BlueprintCallable)
	int CompareStats(float Current, float Next);
};
