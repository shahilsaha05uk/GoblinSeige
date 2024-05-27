// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementActor.h"

#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

APlacementActor::APlacementActor()
{
	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	mStaticMesh->SetupAttachment(RootComponent);
}

void APlacementActor::BeginPlay()
{
	Super::BeginPlay();

	if(const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
		BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::Build);
}

void APlacementActor::UpdateState(EPlacementState State)
{
	switch (State) {
	case EmptyPlacement:
		ToggleMaterial(false);
		ToggleVisibility(true);
		break;
	case SelectedPlacement:
		ToggleMaterial(true);
		break;
	case DeselectedPlacement:
		ToggleMaterial(false);
		break;
	case OccupiedPlacement:
		ToggleMaterial(false);
		ToggleVisibility(false);
		break;
	case DecisionPlacement:
		ToggleMaterial(false);
		ToggleVisibility(false);
		break;
	}

	GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>()->Trigger_OnPlacementStateUpdate(State, this);
}

#pragma region Interfaces

void APlacementActor::Interact_Implementation()
{
	UpdateState(SelectedPlacement);
}

void APlacementActor::Disassociate_Implementation()
{
	UpdateState(DeselectedPlacement);
}

#pragma endregion

#pragma region Builders

void APlacementActor::BuildDummy_Implementation(const FString& BuildingID)
{
	FBuildingBuyDetails BuildingDetails;
	if (DA_BuildingAsset->FindBuildingDetails(BuildingID, BuildingDetails))
	{
		tmpBuildingID = BuildingID;
		FActorSpawnParameters SpawnParams;
		tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingDetails.BuildingClass, GetActorLocation(), GetActorRotation());
		tempBuilding->InitDummy();

		UpdateState(DecisionPlacement);
	}
}

void APlacementActor::Build_Implementation(EBuildStatus Status)
{
	if(!tempBuilding) return;
	tempBuilding->Destroy();

	if(Status == BUILD_CONFIRM)
	{
		FBuildingBuyDetails BuildingDetails;
		if(DA_BuildingAsset->FindBuildingDetails(tmpBuildingID, BuildingDetails))
		{
			tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingDetails.BuildingClass, GetActorLocation(), GetActorRotation());
			tempBuilding->Init(BuildingDetails);

			UpdateState(OccupiedPlacement);
		}
	}
	else
	{
		UpdateState(EmptyPlacement);
	}
	tempBuilding = nullptr;
}

#pragma endregion

#pragma region Togglers

void APlacementActor::ToggleVisibility_Implementation(bool Value)
{
	mStaticMesh->SetVisibility(Value);
}

void APlacementActor::ToggleMaterial_Implementation(bool Value)
{
}

#pragma endregion
