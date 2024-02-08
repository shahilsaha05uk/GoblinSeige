// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/BaseBuilding.h"
#include "GoldActor.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AGoldActor : public ABaseBuilding
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gold Settings")
	int mTotalGold;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gold Settings")
	int mCurrentGold;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gold Settings")
	class UGoldLootBar* GoldLootBar;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LootGold();
	
};
