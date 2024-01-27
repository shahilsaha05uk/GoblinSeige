// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefenceGame/UIClasses/widgets/BuildingUI.h"

ABaseBuilding::ABaseBuilding(const FObjectInitializer& ObjectInitializer)
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
	
	OnBuildingSpawnSignature.AddDynamic(this, &ABaseBuilding::OnBuildingSpawn);
}

void ABaseBuilding::Init_Implementation()
{
	
}

void ABaseBuilding::UpdateBuildingMaterial_Implementation(EPlacementMaterial MatToAdd)
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
		break;
	case PLACING:
		MatToAdd = VALID_MATERIAL;
		bInPlacementMode = true;
		break;
	case PLACED:
		MatToAdd = NO_MATERIAL;
		bInPlacementMode = false;
		break;
	case DESTROYED:
		break;
	case SELECTED:
		MatToAdd = SELECTED_MATERIAL;
		bIsSelected = true;
		//WidgetComp->SetVisibility(true);
		break;
	case DESELECTED:
		MatToAdd = NO_MATERIAL;
		bIsSelected = false;
		//WidgetComp->SetVisibility(false);
		break;
	default:
		MatToAdd = NO_MATERIAL;
		bInPlacementMode = false;
		bIsSelected = false;
		break;
	}

	visibility = bInPlacementMode || bIsSelected;
	
	DecalComp->SetVisibility(visibility);

	UpdateBuildingMaterial(MatToAdd);
}

void ABaseBuilding::OnBuildingSpawn_Implementation()
{
	
}
