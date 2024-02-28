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
	int BuildingID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building Asset Properties")
	FString BuildingName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building Asset Properties")
	int BuildingCost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building Asset Properties")
	UTexture2D* BuildingImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building Asset Properties")
	class UDA_UpgradeAsset* UpgradeAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FBuildingStats BuildingStats;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Building Asset Properties")
	TSubclassOf<class ABaseBuilding> BuildingClass;
};
