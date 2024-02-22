// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameHUD.h"
#include "InputTriggers.h"
#include "UIClasses/PlayerHUD.h"
#include "TowerDefenceGameGameModeBase.h"
#include "ActorComponentClasses/CurrencyComponent.h"
#include "Actors/SpecPlayer.h"
#include "DataAssetClasses/DA_BuildingAsset.h"
#include "InterfaceClasses/HUDInterface.h"
#include "InterfaceClasses/PlayerInputInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ManagerClasses/WaveManager.h"

AInputController::AInputController()
{
	OnBuyMenuOptionClickSignature.AddDynamic(this, &AInputController::OnBuyOptionClicked);
}

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	SpecPawn = Cast<ASpecPlayer>(GetPawn());
	GameHUD = Cast<AGameHUD>(GetHUD());
	GameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode());

	int WaveNumber = -1;

	if(GameMode)
	{
		WaveNumber = GameMode->GetWaveManager()->GetWave(CURRENT_LEVEL);

		GameMode->OnWaveCompleteSignature.AddDynamic(this, &AInputController::OnWaveComplete);
		GameMode->OnEnemyKilledSignature.AddDynamic(this, &AInputController::OnEnemyKilled);
		GameMode->OnGameCompleteSignature.AddDynamic(this, &AInputController::OnGameComplete);
	}
	
	if(GameHUD && UKismetSystemLibrary::DoesImplementInterface(GameHUD, UHUDInterface::StaticClass()))
	{
		PlayerHUD = Cast<UPlayerHUD>(IHUDInterface::Execute_WidgetInitialiser(GameHUD, PLAYER_HUD, this));

		if(PlayerHUD)
		{
			PlayerHUD->OnUpgradeButtonClickedSignature.AddDynamic(this, &AInputController::OnUpgradeButtonClick);
			PlayerHUD->OnMoveButtonClickedSignature.AddDynamic(this, &AInputController::OnMoveButtonClick);
			HUDUpdater(MONEY_VALUE, SpecPawn->CurrencyComponent->GetCurrentBalance());
			HUDUpdater(WAVE_VALUE, WaveNumber);
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
		
		EnhancedInputComponent->BindAction(DA_Inputs->IA_Pause, ETriggerEvent::Completed, this, &AInputController::PauseGame);
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

void AInputController::PauseGame_Implementation()
{
	
}

void AInputController::OnGameComplete_Implementation()
{
	APawn* pawn = GetPawn();

	if(pawn)
	{
		UnPossess();

		pawn->Destroy();
	}

	IHUDInterface::Execute_DestroyWidget(GameHUD, PLAYER_HUD);

	//TODO: Spawn the Game Complete Screen
}

void AInputController::SideWidgetToggler_Implementation(ESideMenuSwitcher menu, ABaseBuilding* BuildingRef, bool isUpgradeAvailable)
{
	PlayerHUD->WidgetToggler(menu, isUpgradeAvailable);
}

void AInputController::OnWaveComplete_Implementation(int WaveNumber)
{
	HUDUpdater(WAVE_VALUE, WaveNumber);
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
	bool bIsOverUI = IHUDInterface::Execute_isCursorHovering(GameHUD);
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

	SpecPawn->SpawnBuilding(BaseBuilding, BuildingAsset);
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

void AInputController::OnEnemyKilled_Implementation()
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInterface::StaticClass()))
	{
		IPlayerInterface::Execute_AddMoneyToAccount(pawn, 100);
		
		HUDUpdater(MONEY_VALUE, IPlayerInterface::Execute_GetCurrentBalance(pawn));
	}
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