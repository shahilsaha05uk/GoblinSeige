// Fill out your copyright notice in the Description page of Project Settings.


#include "DescriptionBox.h"

#include "PlayerHUD.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "TowerDefenceGame/ActorComponentClasses/UpgradeComponent.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "widgets/DescriptionEntry.h"


void UDescriptionBox::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UDescriptionBox::ClearFields()
{
	txtBuildingName->SetText(FText::FromString(""));
	txtCost->SetText(FText::FromString(""));

	entryDamage->ClearFields();
	entryRange->ClearFields();
	entryRateOfFire->ClearFields();
}

void UDescriptionBox::ModifyWhenUnHovered_Implementation()
{
	ClearFields();
}

void UDescriptionBox::ModifyForUpgrade_Implementation(class ABaseBuilding* BuildingRef)
{
	const auto BuildingDetails = BuildingRef->mBuildingDetails;
	const auto UpgradeDetails = BuildingRef->GetUpgradeComp()->GetCurrentUpgrade();

	//constants
	FText name = UHelperMethods::GetTextFromString(BuildingDetails.BuildingName);
	txtBuildingName->SetText(name);

	// upgrade cost
	FText cost = UHelperMethods::GetTextFromString(FString::FromInt(UpgradeDetails.UpgradeCost));
	txtCost->SetText(cost);

	// updates the current stats as well as the next ones
	UpgradeCurrents(BuildingDetails.BuildingStats);
	UpgradeNexts(BuildingDetails.BuildingStats, UpgradeDetails.BuildingStats);
	
}

void UDescriptionBox::ModifyForBuy_Implementation(FBuildingBuyDetails BuildingDetails)
{
	FText name = UHelperMethods::GetTextFromString(BuildingDetails.BuildingName);
	txtBuildingName->SetText(name);

	// buy costs
	FText cost = UHelperMethods::GetTextFromString(FString::FromInt(BuildingDetails.BuildingCost));
	txtCost->SetText(cost);

	// updates the current stats
	UpgradeCurrents(BuildingDetails.BuildingStats);
}

void UDescriptionBox::UpgradeCurrents(FBuildingStats Stats)
{
	FText currentDamage = UHelperMethods::GetTextFromString(FString::FromInt(Stats.Damage));
	entryDamage->UpdateCurrent(currentDamage);

	FText currentRange = UHelperMethods::GetTextFromString(FString::FromInt(Stats.Range));
	entryRange->UpdateCurrent(currentRange);

	FText currentRateOfFire = UHelperMethods::GetTextFromString(FString::FromInt(Stats.RateOfFire));
	entryRateOfFire->UpdateCurrent(currentRateOfFire);

}

void UDescriptionBox::UpgradeNexts(FBuildingStats CurrentStats, FBuildingStats NextStats)
{
	float fCurrent = CurrentStats.Damage;
	float fNext = NextStats.Damage;
	FText nextDamage = UHelperMethods::GetTextFromString(FString::FromInt(fNext));

	entryDamage->UpdateNext(nextDamage, CompareStats(fCurrent, fNext));

	fCurrent = CurrentStats.Range;
	fNext = NextStats.Range;
	FText nextRange = UHelperMethods::GetTextFromString(FString::FromInt(fNext));
	
	entryRange->UpdateNext(nextRange, CompareStats(fCurrent, fNext));

	fCurrent = CurrentStats.RateOfFire;
	fNext = NextStats.RateOfFire;
	FText nextRateOfFire = UHelperMethods::GetTextFromString(FString::FromInt(fNext));

	entryRateOfFire->UpdateNext(nextRateOfFire, CompareStats(fCurrent, fNext));
}

int UDescriptionBox::CompareStats(float Current, float Next)
{
	if(Next < Current) return -1;
	if(Next == Current) return 0;
	else return 1;
}
