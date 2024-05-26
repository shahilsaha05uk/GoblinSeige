// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSubsystem.h"

void UBuildingSubsystem::Trigger_OnBuildingRequestedForBuy(const FString& BuildingID)
{
	OnBuildingRequestedForBuy.Broadcast(BuildingID);
}

void UBuildingSubsystem::Trigger_OnBuildingBought(const FString& BuildingID)
{
	OnBuildingBought.Broadcast(BuildingID);
}

void UBuildingSubsystem::Trigger_OnBuildDecisionTaken(EBuildStatus Status)
{
	OnBuildDecisionTaken.Broadcast(Status);
}

void UBuildingSubsystem::Trigger_OnPlacementActorSelected(APlacementActor* PlacementActor)
{
	OnPlacementActorSelected.Broadcast(PlacementActor);
}

void UBuildingSubsystem::Trigger_OnBuildOnPlacement()
{
	OnBuildOnPlacementActor.Broadcast();
}
