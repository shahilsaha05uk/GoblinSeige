// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacementHandlerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInterface.h"

void UBuildingPlacementHandlerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (const auto World = GetWorld())
    {
        mBuildingPlacementSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>();
        mBuildingSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
        
        if (mBuildingSubsystem)
        {
            mBuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::SpawnBuilding);
        }
    }
}

void UBuildingPlacementHandlerComponent::HandleInteraction()
{
    FHitResult hit;
    const bool Success = GetHit(hit);

    CallDisassociate();

    if(Success)    // if no hit was detected
    {
        auto const owner = GetOwner();
        if (UKismetSystemLibrary::DoesImplementInterface(owner, UPlayerInterface::StaticClass()))
        {
            IPlayerInterface::Execute_RecenterCamera(owner, hit);
        }
        mCurrentHitActor = hit.GetActor();
        CallInteract();
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

void UBuildingPlacementHandlerComponent::SpawnBuilding(const FString& BuildingID)
{
    if(UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UBuildingPlacementInterface::StaticClass()))
    {
       IBuildingPlacementInterface::Execute_Build(mCurrentHitActor, BuildingID);
    }
}

#pragma region Interaction Callers

void UBuildingPlacementHandlerComponent::CallInteract()
{
    // interact with the new actor
    if(UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UInteractableInterface::StaticClass()))
    {
        IInteractableInterface::Execute_Interact(mCurrentHitActor);
    }
}

void UBuildingPlacementHandlerComponent::CallDisassociate()
{
    // deselect the currently hit actor
    if(mCurrentHitActor && UKismetSystemLibrary::DoesImplementInterface(mCurrentHitActor, UInteractableInterface::StaticClass()))
    {
        IInteractableInterface::Execute_Disassociate(mCurrentHitActor);
    }
}

#pragma endregion

