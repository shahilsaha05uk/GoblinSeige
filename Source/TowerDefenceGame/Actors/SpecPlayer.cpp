// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/HelperMethods.h"
#include "TowerDefenceGame/InputController.h"
#include "TowerDefenceGame/ActorComponentClasses/CurrencyComponent.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingInterface.h"

ASpecPlayer::ASpecPlayer()
{
	CurrencyComponent = CreateDefaultSubobject<UCurrencyComponent>(TEXT("CurrencyComponent"));
}

void ASpecPlayer::PossessedBy(AController* NewController)	// Called before BeginPlay
{
	Super::PossessedBy(NewController);

	ControllerRef = Cast<AInputController>(NewController);
}
void ASpecPlayer::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play!! "))
}


void ASpecPlayer::Move_Implementation(const FInputActionValue& InputActionValue)
{
}

void ASpecPlayer::Look_Implementation(const FInputActionValue& InputActionValue)
{
}

void ASpecPlayer::EnableLook_Implementation()
{
}

void ASpecPlayer::DisableLook_Implementation()
{
}

void ASpecPlayer::LeftMouseActions_Implementation()
{
	
	
	if(tempBuilding && tempBuilding->bCanPlace)
	{
		Build();
	}
	else
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		bool bHit;
		FHitResult hit;
		UHelperMethods::GetMouseTrace(PC, BuildingTraceChannel, bHit, hit);

		// Check if hit anything
		if (bHit && hit.bBlockingHit)
		{
			AActor* hitActor = hit.GetActor();

			// Check if the hit actor is the same as the currently selected actor
			if(selectedActor == hitActor) return;

			// Deselect any building if selected
			if(UKismetSystemLibrary::DoesImplementInterface(selectedActor, UBuildingInterface::StaticClass()))
			{
				IBuildingInterface::Execute_Deselect(selectedActor);
				selectedActor = nullptr;
			}
			
			// Select the new hit actor
			if(UKismetSystemLibrary::DoesImplementInterface(hitActor, UBuildingInterface::StaticClass()))
			{
				IBuildingInterface::Execute_Select(hitActor);
				selectedActor = hitActor;
			}
			
			

			// Check if the hit actor implements the building interface
			if (UKismetSystemLibrary::DoesImplementInterface(hitActor, UBuildingInterface::StaticClass()))
			{
				// Deselect previously selected building if any
				/*if (selectBuilding && selectBuilding != hitActor)
				{
					IBuildingInterface::Execute_Deselect(selectBuilding);
					
					ControllerRef->SideWidgetToggler(BUY_MENU);
				}*/

				// Select new building
				//TODO: Revisit this later
				//selectBuilding = Cast<ABaseBuilding>(hitActor);
				
				//if(selectBuilding->bInPlacementMode) return;

				/*
				if(IBuildingInterface::Execute_GetCurrentBuildingState(hitActor) == EBuildingState::PLACING) return;
				
				IBuildingInterface::Execute_Select(selectBuilding, hitActor);

				bool bShouldEnableUpgradeButton = ((selectBuilding->isUpgradeAvailable()) && (CurrencyComponent->GetCurrentBalance() >= selectBuilding->UpgradeAsset->UpgradeCost));
				ControllerRef->SideWidgetToggler(BUILDING_SETTINGS, bShouldEnableUpgradeButton);
			*/
			}
		}
		else
		{
			// Deselect currently selected building if it's valid
			if (selectedActor)
			{
				IBuildingInterface::Execute_Deselect(selectedActor);
				selectedActor = nullptr;
				ControllerRef->SideWidgetToggler(BUY_MENU, nullptr);
			}
		}
	}
}

void ASpecPlayer::Zoom_Implementation(float Value)
{
	
}

void ASpecPlayer::RequestCurrencyUpdate_Implementation(int CurrentBalance)
{
	ControllerRef->HUDUpdater(MONEY_VALUE, CurrentBalance);
}

void ASpecPlayer::SpawnBuilding_Implementation(ABaseBuilding* NewBuilding, UDA_BuildingAsset* BuildingAsset)
{
	tempBuilding = NewBuilding;
	tempBuilding->OnBuildingSelectedSignature.AddDynamic(this, &ThisClass::OnBuildingSelected);

	tempBuilding->Init(BuildingAsset);
}

void ASpecPlayer::Build_Implementation()
{
	if(tempBuilding)
	{
		tempBuilding->Build();
		
		CurrencyComponent->SubtractMoney(tempBuilding->BuildingAsset->BuildingCost);
		ControllerRef->HUDUpdater(MONEY_VALUE, CurrencyComponent->GetCurrentBalance());

		tempBuilding = nullptr;
	}
}

void ASpecPlayer::UpgradeSelectedBuilding_Implementation()
{
	/*if(!selectActor) return;

	int MoneyToDeduct = selectActor->UpgradeAsset->UpgradeCost;
	CurrencyComponent->SubtractMoney(MoneyToDeduct);
	
	selectActor->Upgrade();
	IBuildingInterface::Execute_Deselect(selectActor);

	selectActor = nullptr;
	ControllerRef->SideWidgetToggler(BUY_MENU);*/
	
}

void ASpecPlayer::MoveSelectedBuilding_Implementation()
{
	if(!selectedActor) return;

	IBuildingInterface::Execute_Deselect(selectedActor);

	selectedActor = nullptr;
	ControllerRef->SideWidgetToggler(BUY_MENU, nullptr);
}

void ASpecPlayer::OnBuildingSelected_Implementation(ABaseBuilding* Building)
{
	//TODO: Implement this later

	UE_LOG(LogTemp, Warning, TEXT("On Building Selected"));
	ControllerRef->SideWidgetToggler(BUILDING_SETTINGS, Building);
}
