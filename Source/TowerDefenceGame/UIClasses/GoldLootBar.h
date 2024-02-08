// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoldLootBar.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UGoldLootBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LootGold(int CurrentGoldValue, int TotalGoldValue);
	
};
