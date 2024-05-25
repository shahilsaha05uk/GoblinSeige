// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/ControllerClasses/InputController.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

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
		UHelperMethods::GetMouseTrace(PC, InteractableTraceChannel, bHit, hit);

		// Check if hit anything
		if (bHit && hit.bBlockingHit)
		{
			AActor* hitActor = hit.GetActor();

			// Check if the hit actor is the same as the currently selected actor
			if(selectedActor == hitActor) return;

			// Deselect any building if selected
			ToggleBuildingSelection(selectedActor, false);
			selectedActor = nullptr;

			// Select the new hit actor
			ToggleBuildingSelection(hitActor, false);
			selectedActor = hitActor;
		}
		else
		{
			// Deselect currently selected building if it's valid
			if (selectedActor)
			{
				ToggleBuildingSelection(selectedActor, false);
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
		tempBuilding = nullptr;
	}
}

void ASpecPlayer::UpgradeSelectedBuilding_Implementation(int BuildingID)
{
	/*
	if(!BuildingToUpgrade) return;
	BuildingToUpgrade->Upgrade();
	ToggleBuildingSelection(BuildingToUpgrade, false);
	*/

	ControllerRef->SideWidgetToggler();
	selectedActor = nullptr;
}

void ASpecPlayer::MoveSelectedBuilding_Implementation()
{
	if(!selectedActor) return;
	ToggleBuildingSelection(selectedActor, false);
	selectedActor = nullptr;
	ControllerRef->SideWidgetToggler();
}

void ASpecPlayer::OnBuildingSelected_Implementation(ABaseBuilding* Building)
{
	ControllerRef->SideWidgetToggler(Building);
}

// Selects/Deselects a building
void ASpecPlayer::ToggleBuildingSelection(AActor* Building, bool shouldSelect)
{
	if(UKismetSystemLibrary::DoesImplementInterface(selectedActor, UInteractableInterface::StaticClass()))
	{
		if(shouldSelect) IInteractableInterface::Execute_Interact(Building);
		else IInteractableInterface::Execute_Disassociate(Building);
	}
}