// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "DA_BuildingAsset.generated.h"


UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENCEGAME_API UDA_BuildingAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building Asset Properties")
	TMap<FString, FBuildingBuyDetails> BuildingDetails;


	UFUNCTION(BlueprintCallable)
	bool FindBuildingDetails(FString ID, FBuildingBuyDetails& Building);
};
