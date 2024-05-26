// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSubsystem.h"

void UBuildingSubsystem::Trigger_OnBuildingBought(const FString& BuildingID)
{
	OnBuildingBought.Broadcast(BuildingID);
}
