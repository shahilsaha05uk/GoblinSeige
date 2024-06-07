 // Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "TowerDefenceGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);


UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	class APlayerController* mPlayerController;

	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	int mTotalTargetsToDestroy = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	int mFinalPhase = 2;

	UPROPERTY()
	bool bPhaseChanging = false;
	
	UPROPERTY(EditDefaultsOnly)
	int mStartingResources;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWaveManager> WaveManagerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyManager> EnemyManagerClass;
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Phase", meta = (ToolTip = "Key: Phase; Value: Phase Details"))
	TMap<int, FPhaseDetails> mPhaseDetails;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Phase")
	int mLastPhase;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Phase")
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdatePhase();
	
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
	void MakePhaseDecision();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MakeWaveDecision();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTargets();

	// Decision making methods
	UFUNCTION(BlueprintPure)
	bool HasCompletedAllTheWaves(int Wave = -1) const;
	UFUNCTION(BlueprintPure)
	bool HasDestroyedAllTheTargets() const;
	UFUNCTION(BlueprintPure)
	bool HasPhasesLeft() const;
};
