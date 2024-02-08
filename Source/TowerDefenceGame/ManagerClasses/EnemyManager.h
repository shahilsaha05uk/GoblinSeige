// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnemyController.h"
#include "HAL/CriticalSection.h"
#include "EnemyManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawnRequestSignature, class AEnemySpawnPoint*, SpawnPoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerDestroySignature);



UCLASS()
class TOWERDEFENCEGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()

private:
	int TotalEnemiesDead;

	FCriticalSection Mutex;
	
	TQueue<AEnemyController*> FreeControllers;
	UPROPERTY()
	TArray<AEnemyController*> AllocatedControllers;

	UFUNCTION()
	AEnemyController* GetFreeController();
	UFUNCTION()
	void AssignController(AEnemySpawnPoint* sb);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TSubclassOf<AEnemyController> EnemyControllerClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TArray<AEnemySpawnPoint*> SpawnPoints;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private", meta = (ExposeOnSpawn = true))
	class ATowerDefenceGameGameModeBase* mGameMode;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wave Settings")
	int EnemyMinRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wave Settings")
	int EnemyMaxRange;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemySpawnRequestSignature OnEnemySpawnRequest;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Private")
	FOnControllerDestroySignature OnControllerDestroySignature;

	UFUNCTION()
	void FreeController();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(ATowerDefenceGameGameModeBase* gameMode);


	UFUNCTION(BlueprintCallable)
	void SpawnEnemies(int TotalEnemiesPerSpawnPoints);
	
	UFUNCTION(BlueprintCallable)
	void SpawnControllers(int Count);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetRandomEnemyCounts(int Wave);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGameOver();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PrepareForWave(int Wave);
};
