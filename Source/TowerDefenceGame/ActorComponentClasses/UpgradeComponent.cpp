// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeComponent.h"

#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"


// Sets default values for this component's properties
UUpgradeComponent::UUpgradeComponent()
{

}

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
	MoveToNextUpgrade();
}

bool UUpgradeComponent::IsValidUpgrade() const
{
	return mCurrentUpgrade.UpgradeID != -1;
}

bool UUpgradeComponent::HasNextUpgrade() const
{
	return (!mUpgradeDetails.IsEmpty());
}

void UUpgradeComponent::MoveToNextUpgrade()
{
	if(!mUpgradeDetails.IsEmpty())
	{
		mCurrentUpgrade = mUpgradeDetails[0];
	}
}

void UUpgradeComponent::ApplyUpgrade()
{
	if(!IsValidUpgrade() || mUpgradeDetails.IsEmpty()) return;
	if(mResourceSubsystem)
	{
		mTotalMoneySpentOnUpgrades += mCurrentUpgrade.UpgradeCost;
		mResourceSubsystem->Deduct(mCurrentUpgrade.UpgradeCost);
	}

	mUpgradeDetails.Pop();
	MoveToNextUpgrade();
	OnUpgradeApplied.Broadcast(mCurrentUpgrade);
}

