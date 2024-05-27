// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacementHandlerComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

void UBuildingPlacementHandlerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (const auto World = GetWorld())
    {
        mBuildingPlacementSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>();
        mBuildingSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
        
        if (mBuildingSubsystem)
        {
            mBuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::SpawnDummyBuilding);
        }
    }
}

void UBuildingPlacementHandlerComponent::HandleInteraction()
{
    FHitResult hit;
    const bool Success = GetHit(hit);

    if(!Success)    // if no hit was detected
    {
        // deselect the currently hit actor
        if(mCurrentHitActor && UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UInteractableInterface::StaticClass()))
        {
            IInteractableInterface::Execute_Disassociate(mCurrentHitActor);
        }
    }
    else
    {
        // deselect the currently hit actor
        if(mCurrentHitActor && UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UInteractableInterface::StaticClass()))
        {
            IInteractableInterface::Execute_Disassociate(mCurrentHitActor);
        }

        // set the new hit actor as the current hit actor
        mCurrentHitActor = hit.GetActor();

        // interact with the new actor
        if(UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UInteractableInterface::StaticClass()))
        {
            IInteractableInterface::Execute_Interact(mCurrentHitActor);
        }
    }
}

bool UBuildingPlacementHandlerComponent::GetHit(FHitResult& Hit)
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if(!PC) return false;
    
    bool bHit;
    UHelperMethods::GetMouseTrace(PC, InteractableTraceChannel, bHit, Hit);
    return bHit;
}

void UBuildingPlacementHandlerComponent::SpawnDummyBuilding(const FString& BuildingID)
{
    if(UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UBuildingPlacementInterface::StaticClass()))
    {
        IBuildingPlacementInterface::Execute_BuildDummy(mCurrentHitActor, BuildingID);
    }
}
