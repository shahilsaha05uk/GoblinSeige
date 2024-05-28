// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerUI.h"

#include "Components/Button.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"

void UTowerUI::NativeConstruct()
{
	Super::NativeConstruct();

	btnConfirmPlacement->OnClicked.AddDynamic(this, &ThisClass::OnConfirmPlacement);
	btnAbortPlacement->OnClicked.AddDynamic(this, &ThisClass::OnAbortPlacement);
        

	if (auto const mBuildingPlacementSubsystem = GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>())
	{
		mBuildingPlacementSubsystem->OnPlacementStateUpdate.AddDynamic(this, &ThisClass::OnPlacementStateUpdate);
	}
}

void UTowerUI::OnPlacementStateUpdate_Implementation(EPlacementState State, APlacementActor* PlacementActor)
{
}

void UTowerUI::OnConfirmPlacement_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->Trigger_OnBuildDecisionTaken(BUILD_CONFIRM);
}

void UTowerUI::OnAbortPlacement_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->Trigger_OnBuildDecisionTaken(BUILD_ABORT);
}