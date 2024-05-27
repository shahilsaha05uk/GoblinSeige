// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacementHandlerComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

void UBuildingPlacementHandlerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (const auto World = GetWorld())
    {
        if (const auto BuildingSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
        {
            BuildingSubsystem->OnPlacementActorSelected.AddDynamic(this, &ThisClass::OnPlacementSelected);
            BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::OnBuildingDecisionTaken);
            BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::SpawnDummyBuilding);
        }
    }
}

void UBuildingPlacementHandlerComponent::HandleInteraction()
{
    if(mSelectedPlacement) return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    bool bHit;
    FHitResult Hit;
    UHelperMethods::GetMouseTrace(PC, InteractableTraceChannel, bHit, Hit);

    
    CallDisassociate(mSelectedActor);
    mSelectedActor = nullptr;

    
    if (bHit)
    {
        mSelectedActor = Hit.GetActor();
        if (UKismetSystemLibrary::DoesImplementInterface(mSelectedActor, UInteractableInterface::StaticClass()))
        {
            const auto InteractableType = IInteractableInterface::Execute_GetInteractableType(mSelectedActor);
            if (InteractableType == EInteractableType::BUILDING)
            {
                HandleBuildingInteraction(mSelectedActor);
            }
            else if (InteractableType == EInteractableType::PLACEMENT)
            {
                HandlePlacementInteraction(mSelectedActor);
            }
        }
    }
    else
    {
        mSelectedPlacement = nullptr;
        if (const auto World = GetWorld())
        {
            if (const auto BuildingSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
            {
                BuildingSubsystem->Trigger_OnPlacementActorSelected(nullptr);
            }
        }
    }
}

void UBuildingPlacementHandlerComponent::HandleBuildingInteraction(AActor* HitActor)
{
    if(!HitActor) return;
    CallInteract(HitActor);
}

void UBuildingPlacementHandlerComponent::HandlePlacementInteraction(AActor* HitActor)
{
    if(!HitActor) return;
    CallInteract(HitActor);
}

void UBuildingPlacementHandlerComponent::OnPlacementSelected(APlacementActor* PlacementActor)
{
    mSelectedPlacement = PlacementActor;
}

void UBuildingPlacementHandlerComponent::SpawnDummyBuilding(const FString& BuildingID)
{
    if(mSelectedPlacement)
        mSelectedPlacement->BuildDummy(BuildingID);
}

void UBuildingPlacementHandlerComponent::OnBuildingDecisionTaken(EBuildStatus Status)
{
    switch (Status) {
    case BUILD_CONFIRM:
        mSelectedPlacement = nullptr;
        break;
    case BUILD_ABORT:
        mSelectedPlacement = nullptr;
        if (const auto World = GetWorld())
        {
            if (const auto BuildingSubsystem = World->GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
            {
                BuildingSubsystem->Trigger_OnPlacementActorSelected(nullptr);
            }
        }

        break;
    }
}


// Interface Callers
void UBuildingPlacementHandlerComponent::CallDisassociate(AActor* Target)
{
    if(!Target) return;
    
    if (UKismetSystemLibrary::DoesImplementInterface(Target, UInteractableInterface::StaticClass()))
        IInteractableInterface::Execute_Disassociate(Target);
}

void UBuildingPlacementHandlerComponent::CallInteract(AActor* Target)
{
    if(!Target) return;
    
    if (UKismetSystemLibrary::DoesImplementInterface(Target, UInteractableInterface::StaticClass()))
        IInteractableInterface::Execute_Interact(Target);
}

