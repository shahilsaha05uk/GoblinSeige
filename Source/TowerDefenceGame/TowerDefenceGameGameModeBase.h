// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyKilledSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCompleteSignature, int, waveNumber);

UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	class APlayerController* mPlayerController;

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameCompleteSignature OnGameCompleteSignature;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemyKilledSignature OnEnemyKilledSignature;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameOverSignature OnGameOverSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWaveCompleteSignature OnWaveCompleteSignature;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveComplete(int WaveNumber);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGameOver();


	ATowerDefenceGameGameModeBase();
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AWaveManager* GetWaveManager(){return mWaveManager; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AEnemyManager* GetEnemyManager() { return mEnemyManager; }
	
protected:

	UPROPERTY(BlueprintReadWrite, Category = "Managers")
	class AWaveManager* mWaveManager;
	
	UPROPERTY(BlueprintReadWrite, Category = "Managers")
	class AEnemyManager* mEnemyManager;
};
