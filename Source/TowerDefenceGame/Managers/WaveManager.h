// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/DataAssetClasses/DA_CountdownTimer.h"
#include "WaveManager.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AWaveManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	int Phase2StartWave = 11;

	UPROPERTY(EditDefaultsOnly)
	class UDA_CountdownTimer* mDACountDownTimer;
	UPROPERTY()
	FWaveCountDownTimerDetails mCountDownTimerDetails;


	UPROPERTY(EditDefaultsOnly)
	int mCurrentWave = 1;
	UPROPERTY(EditDefaultsOnly)
	int mFinalWave;
public:

	UPROPERTY(BlueprintReadOnly)
	class ATowerDefenceGameGameModeBase* mGameMode;
	
	UPROPERTY(BlueprintReadOnly)
	class UGameSubsystem* mGameSubsystem;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UTimerComponent* mTimerComp;

	AWaveManager();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RevertWave(int PhaseLostCount);

	UFUNCTION(BlueprintCallable)
	void Init(class ATowerDefenceGameGameModeBase* GameMode);
	UFUNCTION(BlueprintCallable)
	void OnTimerFinish();


	UFUNCTION(BlueprintCallable)
	bool FetchAndUpdateCountdownDetails(int Wave = -1);


	UFUNCTION(BlueprintCallable)
	void OnPhaseReadyToPlay(int PhaseCount);
	UFUNCTION(BlueprintCallable)
	void OnPhaseComplete(int Phase);


	// Wave Management
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentWave(){ return mCurrentWave; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetFinalWave() {return mFinalWave;}
	UFUNCTION(BlueprintCallable)
	void AddWaveCount();
	UFUNCTION(BlueprintCallable)
	void SetWave(int Wave);

	// called when the current wave completes
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void WaveComplete();

	// Starts the next wave
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartNextWave();


	UFUNCTION(BlueprintCallable)
	void OnGameComplete(bool bWon);

};
