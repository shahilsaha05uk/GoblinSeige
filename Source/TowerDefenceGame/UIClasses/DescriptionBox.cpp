// Fill out your copyright notice in the Description page of Project Settings.


#include "DescriptionBox.h"

#include "PlayerHUD.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"


void UDescriptionBox::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UDescriptionBox::UpdateDescriptionWithUpgrade_Implementation(ABaseBuilding* BuildingRef)
{
	
}

void UDescriptionBox::UpdateDescriptionOnHovered_Implementation(FBuildingBuyDetails BuildingDetails)
{
	
}
