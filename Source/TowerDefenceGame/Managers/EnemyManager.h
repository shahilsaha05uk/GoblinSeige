// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"


USTRUCT(BlueprintType)
struct FEnemyStruct
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Easy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Medium;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Hard;
};

USTRUCT(BlueprintType)
struct FWaveStruct
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Min;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Max;
};

USTRUCT(BlueprintType)
struct FWaveEnemyStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int TotalEnemiesToSpawn;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEnemyStruct FixedEnemies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEnemyStruct RandomEnemies;
};




UCLASS()
class TOWERDEFENCEGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()

private:
	int EnemySpawnPointCount = -1;
	int TotalEnemiesToSpawnThisRound = 0;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int, FWaveEnemyStruct> mEnemyMap;
	UPROPERTY()
	TSubclassOf<class AEnemyController> mEnemyControllerClass;

	UPROPERTY()
	FTimerHandle EnemySpawnTimerHandle;
	
	UPROPERTY()
	TArray<class AEnemyController*> mAllocatedController;
	UPROPERTY()
	TArray<class AEnemyController*> mFreeControllers;
	
	UPROPERTY()
	TArray<class AEnemySpawnPoint*> mSpawnPoints;
	
	UPROPERTY(EditDefaultsOnly, Category = "Wave Settings")
	int EnemyMinRange;
	UPROPERTY(EditDefaultsOnly, Category = "Wave Settings")
	int EnemyMaxRange;
	
	UFUNCTION()
	void CacheControllers();
	UFUNCTION()
	void SpawnEnemies();

public:

	UPROPERTY(BlueprintReadOnly)
	class UEnemySubsystem* mEnemySubsystem;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void InitSub(TSubclassOf<AEnemyController> EnemyControllerClass);
	
	UFUNCTION(BlueprintCallable)
	void RequestEnemy();
	UFUNCTION(BlueprintCallable)
	void FreeController(AEnemyController* EnemyController);

	UFUNCTION(BlueprintCallable)
	void PrepareForWave(int Wave);

	UFUNCTION(BlueprintCallable)
	void FlushEverything();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetRandomEnemyCounts(int Wave);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameOver();

};
