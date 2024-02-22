// Fill out your copyright notice in the Description page of Project Settings.


#include "StructClass.h"

#include "DataAssetClasses/DA_BuildingAsset.h"
#include "DataAssetClasses/DA_UpgradeAsset.h"

FBuildingDetails::FBuildingDetails(UDA_BuildingAsset* BuildingAsset)
{
	BuildingName = BuildingAsset->BuildingName;
	UpgradeAsset = BuildingAsset->UpgradeAsset;
	BuildingCost = BuildingAsset->BuildingCost;
	BuildingStats = BuildingAsset->BuildingStats;
}

FBuildingDetails::FBuildingDetails(): UpgradeAsset(nullptr), BuildingCost(0)
{
}

void FBuildingDetails::OnUpgrade()
{
	if(UpgradeAsset)
	{
		BuildingStats += UpgradeAsset->BuildingStats;
	}
}

