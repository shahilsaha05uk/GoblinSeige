// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "MediaSource.h"
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
#include "TowerDefenceGame/Managers/PhaseManager.h"
#include "TowerDefenceGame/SubsystemClasses/BuildingPlacementSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SupportClasses/HelperMethods.h"

AInputController::AInputController()
{
	LevelAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	LevelAudioComp->SetupAttachment(RootComponent);
}

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	
	bShowMouseCursor = true;
	SpecPawn = Cast<ASpecPlayer>(GetPawn());

	const auto hud = GetHUD();
	if(UKismetSystemLibrary::DoesImplementInterface(hud, UHUDInterface::StaticClass()))
	{
		mPlayerHUD = Cast<UPlayerHUD>(IHUDInterface::Execute_WidgetInitialiser(hud, PLAYER_HUD, this));
		if(mPlayerHUD)
			mPlayerHUD->AddToViewport();
	}

	if(const auto PlacementSubs = GetGameInstance()->GetSubsystem<UBuildingPlacementSubsystem>())
	{
		PlacementSubs->OnPlacementStateUpdate.AddDynamic(this, &ThisClass::OnPlacementUpdated);
	}
	
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);
		GameSubs->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoaded);
		GameSubs->OnGameComplete.AddDynamic(this, &ThisClass::OnGameComplete);

		GameSubs->OnFeedbackEnabled.Broadcast(Feed_Success, FString("The Phase Starts in 10 seconds"));
	}

	// setting the min and the max pitch
	PlayerCameraManager->ViewPitchMin = mMinPitch;
	PlayerCameraManager->ViewPitchMax = mMaxPitch;

	/*
	if(const auto gMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gMode->LoadPhase();
	}
	*/
	
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

#pragma region Privates

void AInputController::ReadyToPlay_Implementation()
{
	if(const auto GameMode = Cast<ATowerDefenceGameGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		const int phaseCount = GameMode->mPhaseManager->GetCurrentPhase();
		SetPlayer(phaseCount);
		GameMode->ReadyToPlay();
	}
}

void AInputController::OnGameComplete_Implementation(bool bWon)
{
	SetInputMoveType(UI_Only);
}

void AInputController::ShowCutscene_Implementation(UMediaSource* MediaSource)
{
	
}

#pragma endregion

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

#pragma region Phase

void AInputController::OnPhaseComplete_Implementation(int Phase)
{
	SetIgnoreLookInput(true);
	SetIgnoreLookInput(true);
	DisableInput(this);
}

void AInputController::OnPhaseLoaded_Implementation(int LoadedPhase, FPhaseDetails Details)
{
	ResetIgnoreLookInput();
	ResetIgnoreMoveInput();
	EnableInput(this);

	if(Details.MediaSource)
	{
		ShowCutscene(Details.MediaSource);
	}
	else
	{
		ReadyToPlay();
	}
}

#pragma endregion

#pragma region Getters

FTransform AInputController::GetPlayerStart(int Phase)
{
	const FString str = FString::Printf(TEXT("Phase%d"), Phase);
	auto const actorRef = GetWorld()->GetAuthGameMode()->FindPlayerStart(this, str);
	UE_LOG(LogTemp, Warning, TEXT("Phase Start name: %s"), *actorRef->GetName());
	return GetWorld()->GetAuthGameMode()->FindPlayerStart(this, str)->GetActorTransform();
}

#pragma endregion

#pragma region Setters

void AInputController::SetPlayer_Implementation(int PhaseCount)
{
	// Set the Player
	const FTransform PlayerStartTransform = GetPlayerStart(PhaseCount);
	if (const auto pawn = GetPawn())
	{
		UHelperMethods::SetActorLocationAndControllerRotation(pawn, this, PlayerStartTransform.GetLocation(), PlayerStartTransform.Rotator());
	}
}

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


#pragma endregion
