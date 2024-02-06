// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnemyController.h"
#include "EnemyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawnRequestSignature, class AEnemySpawnPoint*, SpawnPoint);


UCLASS()
class TOWERDEFENCEGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()

private:

	int TotalControllersAvailable;
	
	TQueue<AEnemyController*> AvailableController;
	TMap<uint32, AEnemyController*> AllocatedController;

	UFUNCTION()
	void AllocateController(AEnemySpawnPoint* sb);
	UFUNCTION()
	void FreeController(AEnemyController* ControllerToFree);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TSubclassOf<AEnemyController> EnemyControllerClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TArray<AEnemySpawnPoint*> SpawnPoints;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wave Settings")
	int EnemyMinRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wave Settings")
	int EnemyMaxRange;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemySpawnRequestSignature OnEnemySpawnRequest;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnRequestEnemy();
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemyControllers(int Count);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	void GetRandomEnemyCounts(int &TotalEnemies, int &TotalEnemiesPerSpawnPoints);
};
