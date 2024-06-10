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
	TSubclassOf<class AWaveManager> WaveManagerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyManager> EnemyManagerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APhaseManager> PhaseManagerClass;
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int mStartingResources;
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
	UPROPERTY(BlueprintReadOnly)
	class APhaseManager* mPhaseManager;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameOverSignature OnGameOver;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveUpdated(int Wave);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReadyToPlay();
};
