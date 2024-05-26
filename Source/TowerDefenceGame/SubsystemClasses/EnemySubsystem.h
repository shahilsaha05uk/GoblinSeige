// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemySubsystem.generated.h"


UCLASS()
class TOWERDEFENCEGAME_API UEnemySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	int EnemySpawnPointCount = -1;
	int TotalEnemiesToSpawnThisRound = 0;
	
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

	UFUNCTION()
	void InitSub(TSubclassOf<AEnemyController> EnemyControllerClass);
	
	UFUNCTION(BlueprintCallable)
	void RequestEnemy();
	UFUNCTION(BlueprintCallable)
	void FreeController(AEnemyController* EnemyController);

	// All the spawn points registers themselves with the subsystem at the start of the play 
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnPoint(class AEnemySpawnPoint* SpawnPoint);
	UFUNCTION(BlueprintCallable)
	void DeRegisterSpawnPoint();

	UFUNCTION(BlueprintCallable)
	void PrepareForWave(int Wave);

	UFUNCTION(BlueprintCallable)
	void FlushEverything();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetRandomEnemyCounts(int Wave);
	UFUNCTION(BlueprintPure, BlueprintCallable)
	class AEnemySpawnPoint* GetRandomEnemySpawnPoint();
};
