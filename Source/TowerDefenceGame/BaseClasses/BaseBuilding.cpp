// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"


ABaseBuilding::ABaseBuilding()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	RootComponent = RootComp;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>("CollisionComp");
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseBuilding::OnBuildingBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ABaseBuilding::OnBuildingEndOverlap);

	PlacementDecalComp = CreateDefaultSubobject<UDecalComponent>("Placement Decal");
	PlacementDecalComp->SetupAttachment(BoxComp);
	
	RangeDecalComp = CreateDefaultSubobject<UDecalComponent>("Range Decal");
	RangeDecalComp->SetupAttachment(RootComp);

	RangeCollisionComp = CreateDefaultSubobject<USphereComponent>("RangeCollisionComponent");
	RangeCollisionComp->SetupAttachment(RootComp);
}


void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();

	bCanPlace = false;
	UpdateBuildingState(NO_STATE);

}

void ABaseBuilding::PlaySound_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProjectileSound, GetActorLocation(), GetActorRotation(), 1, 1, 0, nullptr, nullptr, this, nullptr);
}

void ABaseBuilding::Init_Implementation(UDA_BuildingAsset* asset)
{
	BuildingDetails = FBuildingDetails(asset);
	BuildingCost = asset->BuildingCost;

	bCanPlace = true;
	
	IncreaseRange();

	OnMove();
}

void ABaseBuilding::OnBuildingBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Building Overlap Starts: %s"), *OtherActor->GetName());
	bCanPlace = false;
	ChangeBuildingMaterial(INVALID_MATERIAL);

	OverlappingActors.Add(OtherActor);
}

void ABaseBuilding::OnBuildingEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OverlappingActors.Contains(OtherActor)) OverlappingActors.Remove(OtherActor);

	if(!OverlappingActors.IsEmpty()) return;
	
	bCanPlace = true;

	UE_LOG(LogTemp, Warning, TEXT("Building Overlap Ends: %s"), *OtherActor->GetName());
	ChangeBuildingMaterial(VALID_MATERIAL);
	
}


void ABaseBuilding::IncreaseRange_Implementation()
{
	
}

void ABaseBuilding::Upgrade_Implementation()
{
	auto resource = GetGameInstance()->GetSubsystem<UResourceSubsystem>();
	resource->Deduct(BuildingDetails.UpgradeAsset->UpgradeCost);
	
	BuildingDetails.BuildingStats = BuildingDetails.UpgradeAsset->BuildingStats;
	BuildingDetails.UpgradeAsset = BuildingDetails.UpgradeAsset->NextUpgrade;

	UpdateDescription();
	IncreaseRange();
}

void ABaseBuilding::MoveBuilding_Implementation()
{
	if(bInPlacementMode)
	{
		bool bHit;
		FHitResult hit;
		UHelperMethods::GetMouseTrace(UGameplayStatics::GetPlayerController(GetWorld(), 0), BuildingMovementTraceChannel, bHit, hit);

		if(bHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *hit.GetActor()->GetName());
			FVector snappedPos;
			UHelperMethods::CalculateSnappedPosition(hit.Location, 200.0f, snappedPos);
			SetActorLocation(snappedPos);
		}
	}
	else
	{
		OnSpawnTimeHandler.Invalidate();
	}
}

void ABaseBuilding::ChangeBuildingMaterial_Implementation(EPlacementMaterial MatToAdd)
{
	switch (MatToAdd)
	{
	case NO_MATERIAL:
		PlacementDecalComp->SetDecalMaterial(nullptr);
		break;
	case VALID_MATERIAL:
		PlacementDecalComp->SetDecalMaterial(ValidMaterial);
		break;
	case INVALID_MATERIAL:
		PlacementDecalComp->SetDecalMaterial(InvalidMaterial);
		break;
	case SELECTED_MATERIAL:
		PlacementDecalComp->SetDecalMaterial(SelectMaterial);
		break;
	}

}

void ABaseBuilding::UpdateBuildingState_Implementation(EBuildingState State)
{
	BuildingState = State;
	EPlacementMaterial MatToAdd = NO_MATERIAL;
	bool visibility = false;
	
	switch (BuildingState)
	{
	case NO_STATE:
		
		MatToAdd = NO_MATERIAL;
		bInPlacementMode = false;
		bIsSelected = false;
		break;
		
	case PLACING:
		MatToAdd = VALID_MATERIAL;
		bInPlacementMode = true;
		bIsPlaced = false;
		break;
		
	case PLACED:
		
		MatToAdd = NO_MATERIAL;
		bInPlacementMode = false;
		bIsPlaced = true;
		break;
		
	case DESTROYED:
		break;
	case SELECTED:
		
		MatToAdd = SELECTED_MATERIAL;
		bIsSelected = true;
		break;
	case DESELECTED:
		
		MatToAdd = NO_MATERIAL;
		bIsSelected = false;
		break;
		
	default:
		
		MatToAdd = NO_MATERIAL;
		bInPlacementMode = false;
		bIsSelected = false;
		break;
	}

	visibility = bInPlacementMode || bIsSelected;
	
	if(PlacementDecalComp) PlacementDecalComp->SetVisibility(visibility);

	ChangeBuildingMaterial(MatToAdd);
}

int ABaseBuilding::GetUpgradeCost_Implementation()
{
	return (BuildingDetails.UpgradeAsset)? BuildingDetails.UpgradeAsset->UpgradeCost : -1;
}

void ABaseBuilding::OnInteract_Implementation()
{
	UpdateBuildingState(SELECTED);
	OnBuildingSelectedSignature.Broadcast(this);
}

void ABaseBuilding::OnDisassociate_Implementation()
{
	UpdateBuildingState(DESELECTED);
}

void ABaseBuilding::OnMove_Implementation()
{
	UpdateBuildingState(PLACING);
	GetWorld()->GetTimerManager().SetTimer(OnSpawnTimeHandler, this, &ABaseBuilding::MoveBuilding, 0.001f, true);
}

void ABaseBuilding::Build_Implementation()
{
	if(bCanPlace)
	{
		UpdateBuildingState(PLACED);

		auto resource = GetGameInstance()->GetSubsystem<UResourceSubsystem>();
		resource->Deduct(BuildingCost);
		
		PostBuild();
	}
}

void ABaseBuilding::PostBuild_Implementation()
{
	UpdateDescription();
}

void ABaseBuilding::UpdateDescription()
{
	BuildingDescription = UHelperMethods::GetDescription(BuildingDetails.BuildingStats);

	if(BuildingDetails.UpgradeAsset)
		BuildingUpgradeDescription = UHelperMethods::GetUpgradeDescription(BuildingDetails.BuildingStats, BuildingDetails.UpgradeAsset->BuildingStats);
}

void ABaseBuilding::Interact_Implementation()
{
	// Update the building stats
	UDA_UpgradeAsset* up = BuildingDetails.UpgradeAsset;
	if(up)
	{
		auto currentResources = GetGameInstance()->GetSubsystem<UResourceSubsystem>()->GetCurrentResources();
		bCanUpgrade = currentResources >= up->UpgradeCost;
	}
	
	OnInteract();
}

void ABaseBuilding::Disassociate_Implementation()
{
	// Deselecting this building
	UpdateBuildingState(DESELECTED);
	OnDisassociate();
}

