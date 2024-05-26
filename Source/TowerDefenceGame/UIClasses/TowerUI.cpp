// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerUI.h"

#include "Components/Button.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"

void UTowerUI::NativeConstruct()
{
	Super::NativeConstruct();

	btnConfirmPlacement->OnClicked.AddDynamic(this, &ThisClass::OnConfirmPlacement);
	btnAbortPlacement->OnClicked.AddDynamic(this, &ThisClass::OnAbortPlacement);
}

void UTowerUI::OnConfirmPlacement_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->Trigger_OnBuildDecisionTaken(BUILD_CONFIRM);
}

void UTowerUI::OnAbortPlacement_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->Trigger_OnBuildDecisionTaken(BUILD_ABORT);
}