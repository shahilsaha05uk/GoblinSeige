// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>

#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/ControllerClasses/InputController.h"
#include "TowerDefenceGame/InterfaceClasses/HUDInterface.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

void ASpecPlayer::PossessedBy(AController* NewController)	// Called before BeginPlay
{
	Super::PossessedBy(NewController);

	ControllerRef = Cast<AInputController>(NewController);

	if(const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::BuildTower);
		BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::SpawnDummyBuilding);
	}

	// gets and stores the player hud from the HUD class
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
		GameSubs->OnHudInitialised.AddDynamic(this, &ThisClass::OnHudInitialised);

}


void ASpecPlayer::OnHudInitialised(AHUD* HudRef)
{
	if(UKismetSystemLibrary::DoesImplementInterface(HudRef, UHUDInterface::StaticClass()))
	{
		mPlayerHUD = Cast<UPlayerHUD>(IHUDInterface::Execute_GetWidgetReference(HudRef, PLAYER_HUD));
	}
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
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool bHit;
	FHitResult hit;
	UHelperMethods::GetMouseTrace(PC, InteractableTraceChannel, bHit, hit);

	// Deselect the previous actor
	if(mSelectedActor)
	{
		IInteractableInterface::Execute_Disassociate(mSelectedActor);
		mPlayerHUD->ToggleShop(false);
		mSelectedActor = nullptr;
	}
	
	if(bHit)
	{
		mSelectedActor = hit.GetActor();
		if(UKismetSystemLibrary::DoesImplementInterface(mSelectedActor, UInteractableInterface::StaticClass()))
		{
			IInteractableInterface::Execute_Interact(mSelectedActor);
		}
		
		mPlayerHUD->ToggleShop(true);
	}
	
	/*
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
*/
}

void ASpecPlayer::Zoom_Implementation(float Value)
{
	
}

#pragma endregion

void ASpecPlayer::UpgradeSelectedBuilding_Implementation(int BuildingID)
{
	/*
	if(!BuildingToUpgrade) return;
	BuildingToUpgrade->Upgrade();
	ToggleBuildingSelection(BuildingToUpgrade, false);
	*/

	mSelectedActor = nullptr;
}

void ASpecPlayer::MoveSelectedBuilding_Implementation()
{
	if(!mSelectedActor) return;
	ToggleBuildingSelection(mSelectedActor, false);
	mSelectedActor = nullptr;

}

void ASpecPlayer::OnBuildingSelected_Implementation(ABaseBuilding* Building)
{

}

void ASpecPlayer::SpawnDummyBuilding_Implementation(const FString& ID)
{
	FBuildingBuyDetails BuildingDetails;
	if(DA_BuildingAsset->FindBuildingDetails(ID, BuildingDetails))
	{
		tmpBuildingID = ID;
		FActorSpawnParameters spawnParams = FActorSpawnParameters();
		
		tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingDetails.BuildingClass, mSelectedActor->GetActorLocation(), mSelectedActor->GetActorRotation());
		tempBuilding->InitDummy();
	}
}

void ASpecPlayer::BuildTower_Implementation(EBuildStatus Status)
{
	tempBuilding->Destroy();

	if(Status == BUILD_CONFIRM)
	{
		FBuildingBuyDetails BuildingDetails;
		if(DA_BuildingAsset->FindBuildingDetails(tmpBuildingID, BuildingDetails))
		{
			FActorSpawnParameters spawnParams = FActorSpawnParameters();
		
			tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingDetails.BuildingClass, mSelectedActor->GetActorLocation(), mSelectedActor->GetActorRotation());
			tempBuilding->OnBuildingSelectedSignature.AddDynamic(this, &ThisClass::OnBuildingSelected);
			tempBuilding->Init(BuildingDetails);

			if(auto const ResourceSubsystem = GetGameInstance()->GetSubsystem<UResourceSubsystem>())
			{
				ResourceSubsystem->Deduct(BuildingDetails.BuildingCost);
			}
		}
	}

	tempBuilding = nullptr;
}

// Selects/Deselects a building
void ASpecPlayer::ToggleBuildingSelection(AActor* Building, bool shouldSelect)
{
	if(UKismetSystemLibrary::DoesImplementInterface(mSelectedActor, UInteractableInterface::StaticClass()))
	{
		if(shouldSelect) IInteractableInterface::Execute_Interact(Building);
		else IInteractableInterface::Execute_Disassociate(Building);
	}
}

/*
void ASpecPlayer::Build_Implementation()
{
	if(tempBuilding)
	{
		tempBuilding->Build();
		tempBuilding = nullptr;
	}
}*/

