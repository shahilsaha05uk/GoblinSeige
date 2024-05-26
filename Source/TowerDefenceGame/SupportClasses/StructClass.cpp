// Fill out your copyright notice in the Description page of Project Settings.


#include "StructClass.h"

#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"

FBuildingDetails::FBuildingDetails(UDA_BuildingAsset* BuildingAsset): BuildingCost(0), UpgradeAsset(nullptr)
{
	/*
	BuildingName = BuildingAsset->BuildingName;
	UpgradeAsset = BuildingAsset->UpgradeAsset;
	BuildingCost = BuildingAsset->BuildingCost;
	BuildingStats = BuildingAsset->BuildingStats;
*/
}

FBuildingDetails::FBuildingDetails(): UpgradeAsset(nullptr), BuildingCost(0)
{
}

