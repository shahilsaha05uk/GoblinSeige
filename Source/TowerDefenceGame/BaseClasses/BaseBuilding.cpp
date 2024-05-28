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
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
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

void ABaseBuilding::InitDummy_Implementation()
{
	if(const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::OnBuildDecisionTaken);
	}

	RangeDecalComp->SetVisibility(true);
}

void ABaseBuilding::OnBuildDecisionTaken_Implementation(EBuildStatus Status)
{
	switch (Status) {
	case BUILD_CONFIRM:
		{
			const auto objectClass = TSubclassOf<ABaseBuilding>(GetClass());
			const FActorSpawnParameters spawnParams = FActorSpawnParameters();
			GetWorld()->SpawnActor(objectClass, &GetActorTransform(), spawnParams);
		}
		break;
	case BUILD_ABORT:
		{
			Destroy();
		}
		break;
	}
}

void ABaseBuilding::Init_Implementation(FBuildingBuyDetails BuildingDetails)
{
	mBuildingDetails = BuildingDetails;
	BuildingCost = mBuildingDetails.BuildingCost;

	bCanPlace = true;
	RangeDecalComp->SetVisibility(false);

	IncreaseRange();

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
	IncreaseRange();
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


void ABaseBuilding::Build_Implementation()
{
	PostBuild();
}

void ABaseBuilding::PostBuild_Implementation()
{

}

void ABaseBuilding::Interact_Implementation()
{
	// Selecting
	UpdateBuildingState(SELECTED);
	OnBuildingSelectedSignature.Broadcast(this);
	RangeDecalComp->SetVisibility(true);
}

void ABaseBuilding::Disassociate_Implementation()
{
	// Deselecting this building
	UpdateBuildingState(DESELECTED);
	RangeDecalComp->SetVisibility(false);
}

