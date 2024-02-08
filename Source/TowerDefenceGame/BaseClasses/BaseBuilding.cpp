// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/HelperMethods.h"
#include "TowerDefenceGame/UIClasses/widgets/BuildingUI.h"

ABaseBuilding::ABaseBuilding()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	RootComponent = RootComp;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>("CollisionComp");
	BoxComp->SetupAttachment(RootComponent);
	
	DecalComp = CreateDefaultSubobject<UDecalComponent>("DecalComponent");
	DecalComp->SetupAttachment(BoxComp);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComp->SetupAttachment(BoxComp);
	WidgetComp->SetDrawSize(FVector2d(150,20));
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComp->SetWidgetClass(UBuildingUI::StaticClass());
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();

	bCanPlace = false;
	UpdateBuildingState(NO_STATE);
	WidgetComp->SetVisibility(false);
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

void ABaseBuilding::Init_Implementation()
{
	OnBuildingBuildSignature.AddDynamic(this, &ABaseBuilding::OnBuildingBuilt);
	bCanPlace = true;
	UpdateBuildingState(PLACING);
	WidgetComp->SetVisibility(false);
	GetWorld()->GetTimerManager().SetTimer(OnSpawnTimeHandler, this, &ABaseBuilding::MoveBuilding, 0.001f, true);
}

void ABaseBuilding::ChangeBuildingMaterial_Implementation(EPlacementMaterial MatToAdd)
{
	switch (MatToAdd)
	{
	case NO_MATERIAL:
		DecalComp->SetDecalMaterial(nullptr);
		break;
	case VALID_MATERIAL:
		DecalComp->SetDecalMaterial(ValidMaterial);
		break;
	case INVALID_MATERIAL:
		DecalComp->SetDecalMaterial(InvalidMaterial);
		break;
	case SELECTED_MATERIAL:
		DecalComp->SetDecalMaterial(SelectMaterial);
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
		//bIsPlaced = false;
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
		WidgetComp->SetVisibility(true);
		break;
	case DESELECTED:
		MatToAdd = NO_MATERIAL;
		bIsSelected = false;
		WidgetComp->SetVisibility(false);
		break;
	default:
		MatToAdd = NO_MATERIAL;
		bInPlacementMode = false;
		bIsSelected = false;
		break;
	}

	visibility = bInPlacementMode || bIsSelected;
	
	DecalComp->SetVisibility(visibility);

	ChangeBuildingMaterial(MatToAdd);
}

void ABaseBuilding::Build_Implementation()
{
	if(bCanPlace) UpdateBuildingState(PLACED);
}

ABaseBuilding* ABaseBuilding::OnSelect_Implementation(AActor* NewBuilding)
{
	if (!NewBuilding) return nullptr;

	ABaseBuilding* building = Cast<ABaseBuilding>(NewBuilding);
	if (building && building->bIsPlaced)
	{
		building->UpdateBuildingState(SELECTED);
	}

	return building;
}

void ABaseBuilding::Deselect_Implementation()
{
	UpdateBuildingState(DESELECTED);
}

void ABaseBuilding::OnBuildingBuilt_Implementation(int AmmountToDeduct)
{
	Build();

	OnBuildingBuildSignature.RemoveAll(this);
}

