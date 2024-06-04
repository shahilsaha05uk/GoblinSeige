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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseLoadSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseLoadedSuccessfullySignature, int, LoadedPhase);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrepareForPhaseChangeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseChangeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhaseChangeCompleteSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllEnemyDeadSignature);

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

	// Hud
	UPROPERTY()
	AHUD* mHud;

	// Enemy spawn points
	UPROPERTY()
	TArray<class AEnemySpawnPoint*> mSpawnPoints;
	UPROPERTY()
	int EnemySpawnPointCount;

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
	FOnPhaseLoadSignature OnPhaseLoad;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPhaseCompleteSignature OnPhaseComplete;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPhaseLoadedSuccessfullySignature OnPhaseLoadedSuccessfully;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPhaseChangeCompleteSignature OnPhaseChangeComplete;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPhaseChangeSignature OnPhaseChange;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPrepareForPhaseChangeSignature OnPrepareForPhaseChange;

	// Game Decision Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameDecisionMadeSignature OnGameDecisionMade;

	// HUD Delegates
	UPROPERTY(BlueprintAssignable)
	FOnHUDInitialisedSignature OnHudInitialised;

	// Enemy Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FAllEnemyDeadSignature OnAllDead;

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


#pragma region Spawn points
	
	// All the spawn points registers themselves with the subsystem at the start of the play 
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnPoint(class AEnemySpawnPoint* SpawnPoint);
	UFUNCTION(BlueprintCallable)
	void DeRegisterSpawnPoint(class AEnemySpawnPoint* SpawnPoint);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class AEnemySpawnPoint* GetRandomEnemySpawnPoint();

#pragma endregion

};
