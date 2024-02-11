// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/HelperMethods.h"
#include "TowerDefenceGame/InputController.h"
#include "TowerDefenceGame/ActorComponentClasses/CurrencyComponent.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
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

			// Check if the hit actor implements the building interface
			if (UKismetSystemLibrary::DoesImplementInterface(hitActor, UBuildingInterface::StaticClass()))
			{
				// Deselect previously selected building if any
				if (selectBuilding && selectBuilding != hitActor)
				{
					IBuildingInterface::Execute_Deselect(selectBuilding);
				}

				// Select new building
				selectBuilding = Cast<ABaseBuilding>(hitActor);
				IBuildingInterface::Execute_OnSelect(selectBuilding, hitActor);
			}
		}
		else
		{
			// Deselect currently selected building if it's valid
			if (selectBuilding)
			{
				IBuildingInterface::Execute_Deselect(selectBuilding);
				selectBuilding = nullptr;
			}
		}
	}
}

void ASpecPlayer::Zoom_Implementation(float Value)
{
	
}

void ASpecPlayer::RequestCurrencyUpdate_Implementation(int CurrentBalance)
{
	ControllerRef->UpdateCurrency(CurrentBalance);
}

void ASpecPlayer::OnBuildingSpawn_Implementation(ABaseBuilding* NewBuilding)
{
	tempBuilding = NewBuilding;
	tempBuilding->Init();
}

void ASpecPlayer::Build_Implementation()
{
	if(tempBuilding)
	{
		CurrencyComponent->SubtractMoney(tempBuilding->BuildingAsset->BuildingCost);
		tempBuilding->OnBuildingBuildSignature.Broadcast(CurrencyComponent->GetCurrentBalance());
	
		tempBuilding = nullptr;
	}
}

