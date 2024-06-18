// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeComponent.h"

#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"


void UUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		mResourceSubsystem = LocalPlayer->GetSubsystem<UResourceSubsystem>();
	}
}

void UUpgradeComponent::Init(UDA_UpgradeAsset* UpgradeAsset)
{
	if(!UpgradeAsset) return;
	mUpgradeDetails.Append(UpgradeAsset->GetUpgradeDetails());

	// initialising upgrade Indexes
	mTotalAvailableUpgrades = mUpgradeDetails.Num();
	mCurrentUpgradeIndex = 0;

	MoveToNextUpgrade();
}
void UUpgradeComponent::MoveToNextUpgrade()
{
	// setting the next upgrade
	if(mTotalAvailableUpgrades > 0 && mCurrentUpgradeIndex < mTotalAvailableUpgrades)
	{
		mCurrentUpgrade = mUpgradeDetails[mCurrentUpgradeIndex];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Level Reached"));
	}
}

void UUpgradeComponent::ApplyUpgrade()
{
	// deduct the cost from the current balance
	if(mResourceSubsystem)
	{
		mTotalMoneySpentOnUpgrades += mCurrentUpgrade.UpgradeCost;
		mResourceSubsystem->Deduct(mCurrentUpgrade.UpgradeCost);
	}

	// apply the upgrades and move to next upgrades
	OnUpgradeApplied.Broadcast(mCurrentUpgrade);

	// increment the upgrade index
	mCurrentUpgradeIndex++;

	// Move to the next upgrade
	MoveToNextUpgrade();
}

bool UUpgradeComponent::CheckIfUpgradeable()
{
	// if there is upgrade available AND enough bank balance
	return mResourceSubsystem->GetCurrentResources() >= mCurrentUpgrade.UpgradeCost && mCurrentUpgradeIndex < mTotalAvailableUpgrades;
}

