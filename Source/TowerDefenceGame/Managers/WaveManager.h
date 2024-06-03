// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AWaveManager : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	int mInitialWave = 1;
	UPROPERTY(EditDefaultsOnly)
	int mFinalWave;
public:

	UPROPERTY(BlueprintReadOnly)
	class UWaveSubsystem* mWaveSubsystem;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UTimerComponent* mTimerComp;

	AWaveManager();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnTimerFinish();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveComplete(int WaveNumber);


	UFUNCTION(BlueprintCallable)
	void OnPhaseChange();
};
