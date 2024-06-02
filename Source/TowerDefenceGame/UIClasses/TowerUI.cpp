// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerUI.h"

#include "Components/Button.h"
#include "TowerDefenceGame/ActorComponentClasses/UpgradeComponent.h"
#include "TowerDefenceGame/Actors/Tower.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

void UTowerUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	btnConfirmPlacement->OnClicked.AddDynamic(this, &ThisClass::OnConfirmPlacement);
	btnAbortPlacement->OnClicked.AddDynamic(this, &ThisClass::OnAbortPlacement);

	btnUpgradeBuilding->OnClicked.AddDynamic(this, &ThisClass::OnUpgradeBuilding);
	btnDestroyBuilding->OnClicked.AddDynamic(this, &ThisClass::OnDestroyBuilding);

}

void UTowerUI::Init_Implementation(int Cost, class ATower* Tower)
{
	mTowerRef = Tower;
	mBuildingCost = Cost;
	mTowerRef->mUpgradeComp;
}


void UTowerUI::ToggleWidgetSwitcher_Implementation(EDeckType Type)
{
	ActiveDeck = Type;

	if(ActiveDeck == UpgradeWidget)
	{
		UpdateUI();
	}
}

void UTowerUI::UpdateUI_Implementation()
{
	if(const auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		if(auto const ResourceSubs = LocalPlayer->GetSubsystem<UResourceSubsystem>())
		{
			auto const balance = ResourceSubs->GetCurrentResources();
			btnUpgradeBuilding->SetIsEnabled(balance >= mTowerRef->mUpgradeComp->GetCurrentUpgrade().UpgradeCost);
		}
	}
	else
	{
		btnUpgradeBuilding->SetIsEnabled(false);
	}
}

#pragma region Upgrade Methods

void UTowerUI::OnUpgradeBuilding_Implementation()
{
	mTowerRef->mUpgradeComp->ApplyUpgrade();
	ToggleWidgetSwitcher(NoWidget);
}

void UTowerUI::OnDestroyBuilding_Implementation()
{
	mTowerRef->DestructBuilding();
}

#pragma endregion

#pragma region Confirm Methods

void UTowerUI::OnConfirmPlacement_Implementation()
{
	OnDecisionMade.Broadcast(true);
	ToggleWidgetSwitcher(NoWidget);
}

void UTowerUI::OnAbortPlacement_Implementation()
{
	OnDecisionMade.Broadcast(false);
	ToggleWidgetSwitcher(NoWidget);
}

#pragma endregion


