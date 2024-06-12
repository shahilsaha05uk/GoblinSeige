// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementActor.h"

#include "Components/SphereComponent.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

APlacementActor::APlacementActor()
{
	mSphereComp = CreateDefaultSubobject<USphereComponent>("FakeRange");
	mSphereComp->SetupAttachment(RootComponent);

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	mStaticMesh->SetupAttachment(mSphereComp);

}

void APlacementActor::TogglePlacement_Implementation(bool Activate)
{
}

void APlacementActor::BeginPlay()
{
	Super::BeginPlay();

	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
	}
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

ABaseBuilding* APlacementActor::Build_Implementation(const FString& BuildingID)
{
	FBuildingBuyDetails BuildingDetails;
	if (DA_BuildingAsset->FindBuildingDetails(BuildingID, BuildingDetails))
	{
		mBuildingID = BuildingID;
		FActorSpawnParameters SpawnParams;
		mOccupiedBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingTowerClass, GetActorLocation(), GetActorRotation());
		mOccupiedBuilding->OnBuildingDecisionMade.AddDynamic(this, &ThisClass::OnBuildingDecisionTaken);
		mOccupiedBuilding->OnBuildingDestructed.AddDynamic(this, &ThisClass::OnBuildingDestructed);
		mOccupiedBuilding->Init(BuildingDetails, this);

		bIsOccupied = true;
		UpdateState(DecisionPlacement);
	}
	return mOccupiedBuilding;
}

void APlacementActor::OnBuildingDestructed()
{
	mOccupiedBuilding->Destroy();
	bIsOccupied = false;
	UpdateState(EmptyPlacement);
}

void APlacementActor::OnPhaseComplete_Implementation(int Phase)
{
	if(mOccupiedBuilding)
	{
		mOccupiedBuilding->Destroy();
	}
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

#pragma region Privates

void APlacementActor::OnBuildingDecisionTaken_Implementation(bool HasConfirmed)
{
	if(HasConfirmed)
	{
		UpdateState(OccupiedPlacement);
	}
	else
	{
		UpdateState(EmptyPlacement);
		mOccupiedBuilding->Destroy();
	}
}

void APlacementActor::UpdateState(EPlacementState State)
{
	pState = State;
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
	GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>()->OnPlacementStateUpdate.Broadcast(State, this);
}

#pragma endregion

