// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "TowerDefenceGame/Actors/SpecPlayer.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "TowerDefenceGame/BaseClasses/GameHUD.h"
#include "TowerDefenceGame/DataAssetClasses/DA_InputActions.h"
#include "TowerDefenceGame/GameModeClasses/TowerDefenceGameGameModeBase.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ClockSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/UIClasses/GameComplete.h"

AInputController::AInputController()
{
	LevelAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	LevelAudioComp->SetupAttachment(RootComponent);
}

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	if(const auto PlacementSubs = GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>())
	{
		PlacementSubs->OnPlacementStateUpdate.AddDynamic(this, &ThisClass::OnPlacementUpdated);
	}
	
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
		GameSubs->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoadedSuccess);
		GameSubs->OnGameComplete.AddDynamic(this, &ThisClass::OnGameComplete);
	}

	
	bShowMouseCursor = true;
	SpecPawn = Cast<ASpecPlayer>(GetPawn());

	const auto hud = GetHUD();
	if(UKismetSystemLibrary::DoesImplementInterface(hud, UHUDInterface::StaticClass()))
	{
		mPlayerHUD = Cast<UPlayerHUD>(IHUDInterface::Execute_WidgetInitialiser(hud, PLAYER_HUD, this));
		if(mPlayerHUD)
			mPlayerHUD->AddToViewport();
	}

	SetInputMoveType(UI_And_Game);
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

#pragma region Audio Methods

void AInputController::ManageAudio_Implementation(bool hasWaveStarted)
{
	USoundCue* SoundCue = (hasWaveStarted)? WaveCue : BackgroundCue;
	
	LevelAudioComp->FadeOut(2.0f, 0.0f);

	UKismetSystemLibrary::Delay(GetWorld(), 1.0f, FLatentActionInfo());

	LevelAudioComp->SetSound(SoundCue);

	LevelAudioComp->FadeIn(2.0f, 1.0f);
}

void AInputController::PlaySound_Implementation()
{
	ManageAudio(false);
}

void AInputController::StopSound_Implementation()
{
	LevelAudioComp->Stop();
}

void AInputController::OnPlacementUpdated_Implementation(EPlacementState State, APlacementActor* PlacementActor)
{
	if(State == DecisionPlacement)
	{
		SetInputMoveType(UI_Only);
	}
	else
	{
		SetInputMoveType(UI_And_Game);
	}
}
#pragma endregion

#pragma region Control Methods

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
	const auto hud = GetHUD();
	if(UKismetSystemLibrary::DoesImplementInterface(hud, UHUDInterface::StaticClass()))
	{
		if(IHUDInterface::Execute_isCursorHovering(hud)) return;
	}
	
	APawn* pawn = GetPawn();
	
	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_LeftMouseActions(pawn);
	}
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

void AInputController::PauseGame_Implementation()
{
	if(!bIsPaused)
	{
		if(auto pauseWid = IHUDInterface::Execute_WidgetInitialiser(GetHUD(), PAUSE_MENU, this))
		{
			pauseWid->AddToViewport();
			bIsPaused = true;
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}
	else
	{
		IHUDInterface::Execute_DestroyWidget(GetHUD(), PAUSE_MENU);
		bIsPaused = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}
#pragma endregion

void AInputController::SetInputMoveType_Implementation(EInputModeType Type)
{
	switch (Type) {
	case UI_Only:
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
		break;
	case UI_And_Game:
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this);
		break;
	case Game_Only:
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		break;
	}
}

void AInputController::OnPhaseComplete_Implementation(int Phase)
{
	SetIgnoreLookInput(true);
	SetIgnoreLookInput(true);
	DisableInput(this);
}

void AInputController::OnPhaseLoadedSuccess_Implementation(int LoadedPhase)
{
	ResetIgnoreLookInput();
	ResetIgnoreMoveInput();
	EnableInput(this);
}

void AInputController::OnGameComplete_Implementation(bool bWon)
{
	SetInputMoveType(UI_Only);
}
