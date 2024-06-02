// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

#include "TowerDefenceGame/ActorComponentClasses/UpgradeComponent.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

ABaseBuilding::ABaseBuilding()
{
	mStaticMeshSelectedComp = CreateDefaultSubobject<UStaticMeshComponent>("TowerSelection");
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	UpdateBuildingState(NO_STATE);
	bIsPlaced = false;
}

void ABaseBuilding::Init_Implementation(FBuildingBuyDetails BuildingDetails, APlacementActor* PlacementActor)
{
	if(const auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		mResourceSubsystem = LocalPlayer->GetSubsystem<UResourceSubsystem>();
	}
	
	mBuildingDetails = BuildingDetails;

	mPlacement = PlacementActor;
}

void ABaseBuilding::UpdateBuildingState_Implementation(EBuildingState State)
{
	BuildingState = State;
	if(State == SELECTED)
		mStaticMeshSelectedComp->SetVisibility(true);
	else
		mStaticMeshSelectedComp->SetVisibility(false);
}

void ABaseBuilding::Upgrade_Implementation(FUpgradeDetails Details)
{
	
}

void ABaseBuilding::DestructBuilding_Implementation()
{
	if(mResourceSubsystem)
	{
		// total money spent on buying the asset
		int Cost = mBuildingDetails.BuildingCost;

		// this gets the total money spent on the upgrades as well
		if(mUpgradeComp)
			Cost += mUpgradeComp->GetTotalMoneySpentOnUpgrades();

		// calculating the percentage;
		const int deductedCost = Cost - ((DeductionPercentage/100) * Cost);	

		// adding the balance back to the account
		mResourceSubsystem->Add(deductedCost);
	}
}

void ABaseBuilding::Interact_Implementation()
{
	if(!bIsPlaced) return;;
	UpdateBuildingState(SELECTED);
	OnBuildingSelectedSignature.Broadcast(this);
}

void ABaseBuilding::Disassociate_Implementation()
{
	if(!bIsPlaced) return;
	UpdateBuildingState(DESELECTED);
}

void ABaseBuilding::OnBuildingDecisionTaken_Implementation(bool HasConfirmed)
{
	if(HasConfirmed)
	{
		// initialises the building details
		BuildingID = mBuildingDetails.ID;
		BuildingStats = mBuildingDetails.BuildingStats;
		ProjectileClass = mBuildingDetails.mProjectileClass;
		UpgradeAsset = mBuildingDetails.UpgradeAsset;

		// deducts the building cost from the balance
		if(mResourceSubsystem) mResourceSubsystem->Deduct(mBuildingDetails.BuildingCost);
		
		bIsPlaced = true;
	}

	// Notifies all the objects about the building decision
	OnBuildingDecisionMade.Broadcast(HasConfirmed);
}

