// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "BuyButton.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UBuyButton : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BuyButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BuyButtonText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties", meta = (ExposeOnSpawn = true))
	UDA_BuildingAsset* BuildingAsset;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuyButtonClicked();

};
