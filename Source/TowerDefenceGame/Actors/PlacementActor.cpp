// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementActor.h"

#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
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
	{
		BuildingSubsystem->OnBuildOnPlacementActor.AddDynamic(this, &ThisClass::OnBuildOnPlacement);
		BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::Build);

	}
}

void APlacementActor::Interact_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->Trigger_OnPlacementActorSelected(this);
}

void APlacementActor::Disassociate_Implementation()
{
	GetGameInstance()->GetSubsystem<UBuildingSubsystem>()->Trigger_OnPlacementActorSelected(nullptr);
}

void APlacementActor::BuildDummy_Implementation(const FString& BuildingID)
{
	FBuildingBuyDetails BuildingDetails;
	if (DA_BuildingAsset->FindBuildingDetails(BuildingID, BuildingDetails))
	{
		tmpBuildingID = BuildingID;
		FActorSpawnParameters SpawnParams;
		tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingDetails.BuildingClass, GetActorLocation(), GetActorRotation());
		tempBuilding->InitDummy();

		ToggleVisibility(false);
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
			FActorSpawnParameters spawnParams = FActorSpawnParameters();
		
			tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingDetails.BuildingClass, GetActorLocation(), GetActorRotation());
			tempBuilding->Init(BuildingDetails);

			OnBuildOnPlacement();
		}
	}
	else
	{
		ToggleVisibility(true);
	}
	tempBuilding = nullptr;
}

void APlacementActor::OnBuildOnPlacement_Implementation()
{
	ToggleVisibility(false);
}

void APlacementActor::ToggleVisibility_Implementation(bool Value)
{
	mStaticMesh->SetVisibility(Value);
}

