// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "UObject/Object.h"
#include "UpgradeObject.generated.h"


UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENCEGAME_API UUpgradeObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FUpgradeDetails UpgradeDetails;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUpgradeObject> NextUpgrade;
};
