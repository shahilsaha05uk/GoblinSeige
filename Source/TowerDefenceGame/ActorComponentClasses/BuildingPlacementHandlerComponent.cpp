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
            BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::SpawnDummyBuilding);
        }
    }
}

void UBuildingPlacementHandlerComponent::HandleInteraction()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    bool bHit;
    FHitResult Hit;
    UHelperMethods::GetMouseTrace(PC, InteractableTraceChannel, bHit, Hit);

    DeselectCurrentActor();

    if (bHit)
    {
        mSelectedActor = Hit.GetActor();
        if (UKismetSystemLibrary::DoesImplementInterface(mSelectedActor, UInteractableInterface::StaticClass()))
        {
            const auto InteractableType = IInteractableInterface::Execute_GetInteractableType(mSelectedActor);
            if (InteractableType == EInteractableType::BUILDING)
            {
                //HandleBuildingInteraction(mSelectedActor);
            }
            else if (InteractableType == EInteractableType::PLACEMENT)
            {
                HandlePlacementInteraction(mSelectedActor);
            }
        }
    }
}

void UBuildingPlacementHandlerComponent::HandleBuildingInteraction(AActor* HitActor)
{

    /*
    if (ABaseBuilding* Building = Cast<ABaseBuilding>(HitActor))
    {
        if (mSelectedActor)
        {
            IInteractableInterface::Execute_Disassociate(mSelectedActor);
        }
        IInteractableInterface::Execute_Interact(Building);
    }
*/
}

void UBuildingPlacementHandlerComponent::HandlePlacementInteraction(AActor* HitActor)
{
    if(UKismetSystemLibrary::DoesImplementInterface(HitActor, UInteractableInterface::StaticClass()))
    {
        IInteractableInterface::Execute_Interact(HitActor);
    }
}

void UBuildingPlacementHandlerComponent::DeselectCurrentActor()
{
    if (mSelectedActor && UKismetSystemLibrary::DoesImplementInterface(mSelectedActor, UInteractableInterface::StaticClass()))
    {
        IInteractableInterface::Execute_Disassociate(mSelectedActor);
        mSelectedActor = nullptr;
    }
}

void UBuildingPlacementHandlerComponent::OnPlacementSelected(APlacementActor* PlacementActor)
{
    if(PlacementActor)
        mSelectedPlacement = PlacementActor;
}
void UBuildingPlacementHandlerComponent::SpawnDummyBuilding(const FString& BuildingID)
{
    if(mSelectedPlacement)
    {
        mSelectedPlacement->BuildDummy(BuildingID);
    }
}