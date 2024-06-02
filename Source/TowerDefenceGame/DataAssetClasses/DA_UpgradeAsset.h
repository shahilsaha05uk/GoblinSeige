// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "DA_UpgradeAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UDA_UpgradeAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FUpgradeDetails> UpgradeDetails;
public:

	UFUNCTION(BlueprintPure, BlueprintCallable)
	TArray<FUpgradeDetails> GetUpgradeDetails(){return UpgradeDetails;}
	
};
