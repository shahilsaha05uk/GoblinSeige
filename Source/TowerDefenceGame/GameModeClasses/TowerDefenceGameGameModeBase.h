 // Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);

UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	class APlayerController* mPlayerController;

	UPROPERTY(EditDefaultsOnly, Category = "Phase", meta = (ToolTip = "Key: Phase; Value: Total Targets that needs to be breached"))
	TMap<int, int> mPhaseTargetBreachMap;
	
	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	int mTotalTargetsToDestroy = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	int mFinalPhase = 2;
	
	
	UPROPERTY(EditDefaultsOnly)
	int mStartingResources;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWaveManager> WaveManagerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyManager> EnemyManagerClass;
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int, TSoftObjectPtr<UWorld>> mLevelMap;
	UPROPERTY(BlueprintReadWrite, Category = "Phase")
	int mLastPhase;
	UPROPERTY(BlueprintReadWrite, Category = "Phase")
	int mCurrentPhase = 1;

	UPROPERTY(BlueprintReadOnly)
	class UGameSubsystem* mGameSubsystem;

	UPROPERTY(BlueprintReadOnly)
	class AWaveManager* mWaveManager;
	UPROPERTY(BlueprintReadOnly)
	class AEnemyManager* mEnemyManager;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameOverSignature OnGameOver;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LoadPhase();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTargetDestroyed();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameOver();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPhaseLoad();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentPhase() { return mCurrentPhase; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetTotalPhases() {return mFinalPhase; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveUpdated(int Wave);

	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool MakeDecision();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTargets();
};
