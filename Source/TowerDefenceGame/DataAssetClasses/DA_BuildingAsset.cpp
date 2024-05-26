// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_BuildingAsset.h"

bool UDA_BuildingAsset::FindBuildingDetails(FString ID, FBuildingBuyDetails& Building)
{
	if(BuildingDetails.Contains(ID))
	{
		Building = BuildingDetails[ID];
		return true;
	}
	return false;
}
