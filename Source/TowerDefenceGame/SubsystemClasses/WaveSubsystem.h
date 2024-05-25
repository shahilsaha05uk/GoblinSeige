// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WaveSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveUpdateSignature, int, Wave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCompleteSignature, int, Wave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStartSignature, int, Wave);

UCLASS()
class TOWERDEFENCEGAME_API UWaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	int mCurrentWave;
	int mInitialWave;
	int mFinalWave;

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWaveUpdateSignature OnWaveUpdated;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWaveStartSignature OnWaveStarted;
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnWaveCompleteSignature OnWaveComplete;

	UFUNCTION()
	void Init(int initialWave, int finalWave)
	{
		mInitialWave = initialWave;
		mFinalWave = finalWave;
		mCurrentWave = mInitialWave;
		OnWaveUpdated.Broadcast(mCurrentWave);
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentWave(){ return mCurrentWave; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetFinalWave() {return mFinalWave;}
	UFUNCTION(BlueprintCallable)
	void AddWaveCount()
	{
		mCurrentWave++;
		OnWaveUpdated.Broadcast(mCurrentWave);
	}

	UFUNCTION(BlueprintCallable)
	void StartWave();
	UFUNCTION(BlueprintCallable)
	void EndWave();
};
