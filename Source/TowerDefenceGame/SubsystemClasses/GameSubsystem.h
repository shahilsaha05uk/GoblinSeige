// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "GameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameDecisionMadeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDInitialisedSignature, AHUD*, HudRef);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFeedbackSystemEnableSignature, EFeedbackType, Type, const FString&, MessageToDisplay);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameCompleteSignature, bool, bWon);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseCompleteSignature, int, Phase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseLoadedSuccessfullySignature, int, LoadedPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhaseReadyToPlaySignature, int, PhaseCount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllEnemyDeadSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemiesReadySignature, int, TotalEnemies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDieSignature, class AEnemyController*, Controller);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetDestroyedSignature);
// Wave Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCompletedSignature, int, Wave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStartSignature, int, Wave);
DECLARE_DYNAMIC_DELEGATE_RetVal(int, FGetCurrentWaveSignature);




UCLASS()
class TOWERDEFENCEGAME_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	UPROPERTY()
	AHUD* mHud;

public:

	// Enemy when they destroy a target
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTargetDestroyedSignature OnTargetDestroyed;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnFeedbackSystemEnableSignature OnFeedbackEnabled;

	// Game Events
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameCompleteSignature OnGameComplete;

	// Phase Events
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPhaseCompleteSignature OnPhaseComplete;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPhaseLoadedSuccessfullySignature OnPhaseLoadedSuccessfully;

	// On Ready to play
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPhaseReadyToPlaySignature OnPhaseReadyToPlay;

	// Game Decision Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameDecisionMadeSignature OnGameDecisionMade;

	// HUD Delegates
	UPROPERTY(BlueprintAssignable)
	FOnHUDInitialisedSignature OnHudInitialised;

	// Enemy Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemiesReadySignature OnEnemiesReady;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FAllEnemyDeadSignature OnAllDead;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemyDieSignature OnEnemyDie;

	// Wave Delegates
	UPROPERTY()
	FGetCurrentWaveSignature OnGetCurrentWave;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWaveCompletedSignature OnWaveUpdated;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWaveStartSignature OnWaveStarted;
	
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AHUD* GetHudRef() {return mHud;}
	
	UFUNCTION(BlueprintCallable)
	void InitialiseHud(AHUD* HudRef)
	{
		mHud = HudRef;
		OnHudInitialised.Broadcast(mHud);
	}
	
};
