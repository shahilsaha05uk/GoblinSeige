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

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Next Skill")
	TMap<int, FUpgradeDetails> UpgradeDetails;
};
