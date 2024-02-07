// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../EnumClass.h"
#include "WaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveUpdateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveStartSignature);

UCLASS()
class TOWERDEFENCEGAME_API AWaveManager : public AActor
{
	GENERATED_BODY()


private:
	
	int mInitialWave;
	int mCurrentWave;
	int mFinalWave;


public:	
	AWaveManager();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWaveStartSignature OnWaveStartSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWaveUpdateSignature OnWaveUpdateSignature;

	UFUNCTION(BlueprintCallable)
	int GetWave(ELevel level);
	
	UFUNCTION(BlueprintCallable)
	void UpdateWave();



};
