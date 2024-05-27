// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacementSubsystem.h"

void UBuildingPlacementSubsystem::Trigger_OnPlacementStateUpdate(EPlacementState State, APlacementActor* PlacementActor)
{
	OnPlacementStateUpdate.Broadcast(State, PlacementActor);
}
