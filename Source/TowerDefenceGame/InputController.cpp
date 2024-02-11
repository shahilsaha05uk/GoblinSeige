// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameHUD.h"
#include "InputTriggers.h"
#include "TowerDefenceGameGameModeBase.h"
#include "ActorComponentClasses/CurrencyComponent.h"
#include "Actors/SpecPlayer.h"
#include "DataAssetClasses/DA_BuildingAsset.h"
#include "InterfaceClasses/PlayerInputInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ManagerClasses/WaveManager.h"
#include "UIClasses/PlayerHUD.h"

AInputController::AInputController()
{
	bIsOverUI = false;
	
	OnBuyMenuOptionClickSignature.AddDynamic(this, &AInputController::OnBuyOptionClicked);
}

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	SpecPawn = Cast<ASpecPlayer>(GetPawn());
	GameHUD = Cast<AGameHUD>(GetHUD());
	GameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());

	if(GameMode)
	{
		GameMode->OnWaveCompleteSignature.AddDynamic(this, &AInputController::OnWaveComplete);
	}
	
	if(GameHUD)
	{
		int WaveNumber = -1;
		if(GameMode)
		{
			WaveNumber = GameMode->GetWaveManager()->GetWave(CURRENT_LEVEL);
		}
		PlayerHUD = Cast<UPlayerHUD>(GameHUD->WidgetInitialiser(PLAYER_HUD, this));

		if(PlayerHUD)
		{
			PlayerHUD->OnUpgradeButtonClickedSignature.AddDynamic(this, &AInputController::OnUpgradeButtonClick);
			PlayerHUD->OnMoveButtonClickedSignature.AddDynamic(this, &AInputController::OnMoveButtonClick);
			UpdateCurrency(SpecPawn->CurrencyComponent->GetCurrentBalance());
			PlayerHUD->UpdateWave(WaveNumber);
			PlayerHUD->AddToViewport();
		}
		
	}
}

void AInputController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		
		//Moving
		EnhancedInputComponent->BindAction(DA_Inputs->IA_SpMove, ETriggerEvent::Triggered, this, &AInputController::Move);
		EnhancedInputComponent->BindAction(DA_Inputs->IA_SpLook, ETriggerEvent::Triggered, this, &AInputController::Look);

		EnhancedInputComponent->BindAction(DA_Inputs->IA_SpEnableLook, ETriggerEvent::Triggered, this, &AInputController::EnableLook);
		EnhancedInputComponent->BindAction(DA_Inputs->IA_SpEnableLook, ETriggerEvent::Completed, this, &AInputController::DisableLook);
		
		EnhancedInputComponent->BindAction(DA_Inputs->IA_LeftMouseActions, ETriggerEvent::Completed, this, &AInputController::LeftMouseActions);

		EnhancedInputComponent->BindAction(DA_Inputs->IA_Zoom, ETriggerEvent::Triggered, this, &AInputController::Zoom);
		
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AInputController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}



void AInputController::SideWidgetToggler_Implementation(ESideMenuSwitcher menu, bool isUpgradeAvailable)
{
	PlayerHUD->WidgetToggler(menu, isUpgradeAvailable);
}

void AInputController::OnWaveComplete_Implementation(int WaveNumber)
{
	PlayerHUD->UpdateWave(WaveNumber);
}

void AInputController::UpdateCurrency_Implementation(int CurrentBalance)
{
	PlayerHUD->UpdateMoney(CurrentBalance);
}

void AInputController::Zoom_Implementation(const FInputActionValue& InputActionValue)
{
	APawn* pawn = GetPawn();
	
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		float Value = InputActionValue.Get<float>();
		IPlayerInputInterface::Execute_Zoom(pawn, Value);
	}
}

void AInputController::LeftMouseActions_Implementation()
{
	if(bIsOverUI) return;
	
	APawn* pawn = GetPawn();
	
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_LeftMouseActions(pawn);
	}

}

void AInputController::OnBuyOptionClicked_Implementation(UDA_BuildingAsset* BuildingAsset)
{
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	ABaseBuilding* BaseBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingAsset->BuildingClass, spawnParams);

	BaseBuilding->BuildingAsset = BuildingAsset;
	BaseBuilding->OnBuildingBuildSignature.AddDynamic(this, &AInputController::OnBuildingBuilt);

	SpecPawn->OnBuildingSpawn(BaseBuilding);
}

void AInputController::Move_Implementation(const FInputActionValue& InputActionValue)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Move(pawn, InputActionValue);
	}
}

void AInputController::Look_Implementation(const FInputActionValue& InputActionValue)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Look(pawn, InputActionValue);
	}
}

void AInputController::EnableLook_Implementation(const FInputActionValue& InputActionValue)
{
	APawn* pawn = GetPawn();
	
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_EnableLook(pawn);
		bShowMouseCursor = false;
	}
}

void AInputController::DisableLook_Implementation(const FInputActionValue& InputActionValue)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_DisableLook(pawn);
		bShowMouseCursor = true;
	}
}


void AInputController::OnBuildingBuilt_Implementation(int CurrentBalance)
{
	PlayerHUD->UpdateMoney(CurrentBalance);
}


void AInputController::OnUpgradeButtonClick_Implementation()
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInterface::StaticClass()))
	{
		IPlayerInterface::Execute_UpgradeSelectedBuilding(pawn);
	}
}

void AInputController::OnMoveButtonClick_Implementation()
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInterface::StaticClass()))
	{
		IPlayerInterface::Execute_MoveSelectedBuilding(pawn);
	}
}