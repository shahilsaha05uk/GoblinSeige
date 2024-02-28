// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/ActorComponentClasses/CurrencyComponent.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/ControllerClasses/InputController.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingInterface.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

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
}

#pragma region Input

void ASpecPlayer::Move_Implementation(const FInputActionValue& InputActionValue)
{
	FVector vec = InputActionValue.Get<FVector>();

	FRotator cachedRot = GetControlRotation();
	
	FRotator fwdRot = cachedRot; fwdRot.Roll = fwdRot.Pitch = 0;
	FRotator rhtRot = cachedRot; rhtRot.Pitch = 0;
	
	FVector fwdVec = fwdRot.Vector();
	FVector rhtVec = FRotationMatrix(rhtRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(fwdVec, vec.X);
	AddMovementInput(rhtVec, vec.Y);
}

void ASpecPlayer::Look_Implementation(const FInputActionValue& InputActionValue)
{
	float yaw = InputActionValue.Get<FVector>().X;
	AddControllerYawInput(yaw);
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
	else if(!tempBuilding)
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
				IBuildingInterface::Execute_Select(hitActor, Execute_GetCurrentBalance(this));
				selectedActor = hitActor;
			}
		}
		else
		{
			// Deselect currently selected building if it's valid
			if (selectedActor)
			{
				IBuildingInterface::Execute_Deselect(selectedActor);
				selectedActor = nullptr;
				ControllerRef->SideWidgetToggler();
			}
		}
	}
}

void ASpecPlayer::Zoom_Implementation(float Value)
{
	
}

#pragma endregion

#pragma region Player Interface Methods

void ASpecPlayer::RequestCurrencyUpdate_Implementation(int CurrentBalance)
{
	ControllerRef->HUDUpdater(MONEY_VALUE, CurrentBalance);
}

#pragma endregion

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
		
		CurrencyComponent->SubtractMoney(tempBuilding->BuildingCost);
		Execute_RequestCurrencyUpdate(this, CurrencyComponent->GetCurrentBalance());
		tempBuilding = nullptr;
	}
}

void ASpecPlayer::UpgradeSelectedBuilding_Implementation(ABaseBuilding* BuildingToUpgrade, int UpgradeCost)
{
	if(!BuildingToUpgrade) return;
	
	CurrencyComponent->SubtractMoney(UpgradeCost);
	
	BuildingToUpgrade->Upgrade();
	
	if(IBuildingInterface::Execute_GetCurrentBuildingState(BuildingToUpgrade) == SELECTED)
		IBuildingInterface::Execute_Deselect(BuildingToUpgrade);

	Execute_RequestCurrencyUpdate(this, CurrencyComponent->GetCurrentBalance());
	ControllerRef->SideWidgetToggler();

	selectedActor = nullptr;
}

void ASpecPlayer::MoveSelectedBuilding_Implementation()
{
	if(!selectedActor) return;

	IBuildingInterface::Execute_Deselect(selectedActor);

	selectedActor = nullptr;
	ControllerRef->SideWidgetToggler();
}

void ASpecPlayer::OnBuildingSelected_Implementation(ABaseBuilding* Building)
{
	ControllerRef->SideWidgetToggler(Building);
}
