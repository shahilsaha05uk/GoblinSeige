// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>

#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/PlacementSubsystem.h"
#include "TowerDefenceGame/ActorComponentClasses/BuildingPlacementHandlerComponent.h"
#include "TowerDefenceGame/ControllerClasses/InputController.h"
#include "TowerDefenceGame/InterfaceClasses/HUDInterface.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingSubsystem.h"

ASpecPlayer::ASpecPlayer()
{
	mBuildingPlacementHandlerComponent = CreateDefaultSubobject<UBuildingPlacementHandlerComponent>("PlayerInteractionComponent");
}

void ASpecPlayer::PossessedBy(AController* NewController)	// Called before BeginPlay
{
	Super::PossessedBy(NewController);

	ControllerRef = Cast<AInputController>(NewController);
	// gets and stores the player hud from the HUD class
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
		GameSubs->OnHudInitialised.AddDynamic(this, &ThisClass::OnHudInitialised);


	if (const auto BuildingSubsystem = GetGameInstance()->GetSubsystem<UBuildingSubsystem>())
	{
		//BuildingSubsystem->OnPlacementActorSelected.AddDynamic(this, &ThisClass::OnPlacementSelected);
		//BuildingSubsystem->OnBuildingRequestedForBuy.AddDynamic(this, &ThisClass::OnRequestForBuildingBuy);
		//BuildingSubsystem->OnBuildDecisionTaken.AddDynamic(this, &ThisClass::OnBuildingDecisionTaken);
	}
	if (const auto PlacementSubs = GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>())
	{
		PlacementSubs->OnPlacementStateUpdate.AddDynamic(this, &ThisClass::OnPlacementStateUpdated);
	}
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
	mBuildingPlacementHandlerComponent->HandleInteraction();
}

void ASpecPlayer::Zoom_Implementation(float Value)
{
	
}

#pragma endregion

#pragma region Placement Actor Selection Methods

void ASpecPlayer::UpgradeSelectedBuilding_Implementation(int BuildingID)
{
	/*
	if(!BuildingToUpgrade) return;
	BuildingToUpgrade->Upgrade();
	ToggleBuildingSelection(BuildingToUpgrade, false);
	*/
}

void ASpecPlayer::OnPlacementStateUpdated(EPlacementState State, APlacementActor* PlacementActor)
{
	//switch (State) {  }
}

#pragma endregion

// Selects/Deselects a building

/*
void ASpecPlayer::ToggleBuildingSelection(AActor* Building, bool shouldSelect)
{
}
void ASpecPlayer::Build_Implementation()
{
	if(tempBuilding)
	{
		tempBuilding->Build();
		tempBuilding = nullptr;
	}
}*/

