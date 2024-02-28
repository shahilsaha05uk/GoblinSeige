// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGame/InterfaceClasses/GameModeInterface.h"
#include "TowerDefenceGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyKilledSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCompleteSignature, int, waveNumber);

UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase, public IGameModeInterface
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
	
	virtual AWaveManager* GetWaveManager_Implementation() override {return mWaveManager;}
	virtual AEnemyManager* GetEnemyManager_Implementation() override {return mEnemyManager; }

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Managers")
	class AWaveManager* mWaveManager;
	
	UPROPERTY(BlueprintReadWrite, Category = "Managers")
	class AEnemyManager* mEnemyManager;
};
