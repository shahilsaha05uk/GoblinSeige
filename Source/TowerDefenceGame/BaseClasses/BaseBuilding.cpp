// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

#include "NiagaraComponent.h"
#include "TowerDefenceGame/ActorComponentClasses/UpgradeComponent.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

ABaseBuilding::ABaseBuilding()
{
	mStaticMeshSelectedComp = CreateDefaultSubobject<UStaticMeshComponent>("TowerSelection");

	mNiagaraUpgradeComp = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComp");
}

void ABaseBuilding::Init_Implementation(FBuildingBuyDetails BuildingDetails, APlacementActor* PlacementActor)
{
	if(const auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		mResourceSubsystem = LocalPlayer->GetSubsystem<UResourceSubsystem>();
	}
	mBuildingDetails = BuildingDetails;

	mPlacement = PlacementActor;

	mStaticMeshSelectedComp->SetVisibility(false);
	bIsPlaced = false;
}

#pragma region Interactions

void ABaseBuilding::Interact_Implementation()
{
	if(!bIsPlaced) return;;
	mStaticMeshSelectedComp->SetVisibility(true);

	if(const auto BuildingSubs = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		BuildingSubs->OnBuildingInteractionBegin.Broadcast(this);
	}
}

void ABaseBuilding::Disassociate_Implementation()
{
	if(!bIsPlaced) return;
	mStaticMeshSelectedComp->SetVisibility(false);

	if(const auto BuildingSubs = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		BuildingSubs->OnBuildingInteractionEnd.Broadcast(this);
	}
}

#pragma endregion

#pragma region Upgrade

void ABaseBuilding::Upgrade_Implementation(FUpgradeDetails Details)
{
	Execute_Disassociate(this);
}

#pragma endregion

#pragma region Destruction

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

	OnBuildingDestructed.Broadcast();
}

#pragma endregion

#pragma region Privates

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

#pragma endregion
