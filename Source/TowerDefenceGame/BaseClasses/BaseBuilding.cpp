// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"

ABaseBuilding::ABaseBuilding()
{
	mStaticMeshSelectedComp = CreateDefaultSubobject<UStaticMeshComponent>("TowerSelection");
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	UpdateBuildingState(NO_STATE);

	if(const auto BuildingSubs = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
		BuildingSubs->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::OnBuildingDecisionTaken);
}

void ABaseBuilding::Init_Implementation(FBuildingBuyDetails BuildingDetails)
{
	mBuildingDetails = BuildingDetails;
}

void ABaseBuilding::Upgrade_Implementation()
{
	
}

void ABaseBuilding::UpdateBuildingState_Implementation(EBuildingState State)
{
	BuildingState = State;

	// Changing the Material on the building
	if(BuildingState == SELECTED)
		mStaticMeshSelectedComp->SetVisibility(true);
	else
		mStaticMeshSelectedComp->SetVisibility(false);
}


void ABaseBuilding::Interact_Implementation()
{
	UpdateBuildingState(SELECTED);
	OnBuildingSelectedSignature.Broadcast(this);
}

void ABaseBuilding::Disassociate_Implementation()
{
	UpdateBuildingState(DESELECTED);
}

void ABaseBuilding::OnBuildingDecisionTaken_Implementation(EBuildStatus Status)
{
	if(Status == BUILD_CONFIRM)
	{
		BuildingID = mBuildingDetails.ID;
		BuildingStats = mBuildingDetails.BuildingStats;
		ProjectileClass = mBuildingDetails.mProjectileClass;
		UpgradeAsset = mBuildingDetails.UpgradeAsset;
	}
}
