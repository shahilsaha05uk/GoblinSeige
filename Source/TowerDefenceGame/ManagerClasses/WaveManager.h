// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyManager.h"
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
	UPROPERTY(EditDefaultsOnly)
	int mInitialWave;
	UPROPERTY(EditDefaultsOnly)
	int mFinalWave;
	
	int mCurrentWave;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave Properties")
	FOnWaveUpdateSignature OnWaveUpdateSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave Properties")
	FOnWaveStartSignature OnWaveStartSignature;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private", meta = (ExposeOnSpawn = true))
	class ATowerDefenceGameGameModeBase* mGameMode;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(ATowerDefenceGameGameModeBase* gameMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartWave();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndWave();

	UFUNCTION(BlueprintCallable)
	int GetWave(ELevel level);
	
	UFUNCTION(BlueprintCallable)
	void UpdateWave();
};
