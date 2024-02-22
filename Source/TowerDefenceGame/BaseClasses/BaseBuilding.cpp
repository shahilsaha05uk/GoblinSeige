// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/HelperMethods.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/UIClasses/widgets/BuildingUI.h"


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

void ABaseBuilding::Init_Implementation(UDA_BuildingAsset* asset)
{
	this->BuildingAsset = asset;
	UpgradeAsset = BuildingAsset->UpgradeAsset;
	
	bCanPlace = true;
	UpdateBuildingState(PLACING);

	IncreaseRange();
	
	GetWorld()->GetTimerManager().SetTimer(OnSpawnTimeHandler, this, &ABaseBuilding::MoveBuilding, 0.001f, true);
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

bool ABaseBuilding::isUpgradeAvailable_Implementation()
{
	return UpgradeAsset != nullptr;
}

bool ABaseBuilding::isFullyUpgraded()
{
	return (UpgradeAsset == nullptr);
}

void ABaseBuilding::IncreaseRange_Implementation()
{
	
}

void ABaseBuilding::Upgrade_Implementation()
{
	UpgradeAsset = UpgradeAsset->NextUpgrade;

	if(isFullyUpgraded()) OnBuildingFullyUpgradedSignature.Broadcast();
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

/*
ABaseBuilding* ABaseBuilding::Select_Implementation(AActor* NewBuilding)
{
	if (!NewBuilding) return nullptr;

	ABaseBuilding* building = Cast<ABaseBuilding>(NewBuilding);
	if (building && building->bIsPlaced)
	{
		building->UpdateBuildingState(SELECTED);
		//WidgetComp->SetVisibility(true);
	}

	OnSelect();
	return building;
}

*/
void ABaseBuilding::Select_Implementation()
{
	OnSelect();
}

void ABaseBuilding::Deselect_Implementation()
{
	UpdateBuildingState(DESELECTED);

	OnDeselect();
}

void ABaseBuilding::OnSelect_Implementation()
{
	UpdateBuildingState(SELECTED);
	OnBuildingSelectedSignature.Broadcast(this);
}

/*
void ABaseBuilding::OnSelect_Implementation()
{
}

*/
void ABaseBuilding::OnDeselect_Implementation()
{
	UpdateBuildingState(DESELECTED);
}

void ABaseBuilding::UpdateBuildingStats_Implementation(FBuildingStats stats)
{
}

void ABaseBuilding::Build_Implementation()
{
	if(bCanPlace) UpdateBuildingState(PLACED);

	//OnTurretActivateSignature.Broadcast();

	PostBuild();
}

void ABaseBuilding::PostBuild_Implementation()
{
	
}