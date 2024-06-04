// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"


USTRUCT(BlueprintType)
struct FFixedEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fixed Enemy")
	int32 EnemyLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fixed Enemy")
	int32 Count;
};

USTRUCT(BlueprintType)
struct FEnemyProbability
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Probability")
	int32 EnemyLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Probability", meta = (ClampMin = "0.0", ClampMax = "1.0", SliderExponent))
	float Probability;
};


USTRUCT(BlueprintType)
struct FWaveRangeConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave Range Config")
	int32 StartWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave Range Config")
	int32 EndWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave Range Config")
	int32 TotalEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave Range Config")
	TArray<FFixedEnemy> FixedEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave Range Config")
	TArray<FEnemyProbability> EnemyProbabilities;
};

UCLASS()
class TOWERDEFENCEGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyController> mEnemyControllerClass;

	UPROPERTY()
	bool bPhaseComplete;
	UPROPERTY()
	int TotalEnemyControllersAssigned = 0;
	UPROPERTY()
	FTimerHandle EnemySpawnTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category="Wave Configurations")
	TMap<int, FWaveRangeConfig> WaveRangeConfigurations;

	
	UPROPERTY()
	TArray<class AEnemySpawnPoint*> mSpawnPoints;
	
public:
	UPROPERTY(BlueprintReadWrite)
	int TotalEnemyControllers = 0;
	UPROPERTY(BlueprintReadWrite)
	TArray<class AEnemyController*> mFreeControllers;


	
	UPROPERTY(BlueprintReadOnly)
	class UEnemySubsystem* mEnemySubsystem;
	UPROPERTY(BlueprintReadOnly)
	class UWaveSubsystem* mWaveSubsystem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int mRemainingEnemies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FWaveRangeConfig mLatestWaveConfigs;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CacheControllers(int ControllerCount);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AssignEnemy(int EnemyID);
	UFUNCTION(BlueprintCallable)
	void FreeController(class AEnemyController* ControllerRef);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PrepareForWave(int Wave);

	UFUNCTION(BlueprintCallable)
	void FlushEverything();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	TMap<int, FWaveRangeConfig> GetWaveConfigs() {return WaveRangeConfigurations;}
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameOver();

	// Spawners
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasEnoughControllers(int &RequiredControllers);
	UFUNCTION(BlueprintCallable)
	void NormalizeProbabilities(TArray<FEnemyProbability>& Probabilities);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnFixedEnemies(const TArray<FFixedEnemy> &FixedEnemyData);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnProbableEnemies(const TArray<FEnemyProbability> &ProbableData);


	// Phase
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPhaseChangeComplete();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPrepareForPhaseChange();






};
