// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDefenceGame/ActorComponentClasses/BaseSkillComponent.h"
#include "DA_UpgradeAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UDA_UpgradeAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UpgradeID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UpgradeName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseSkillComponent> SkillClass;
	
};
