// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:

	class AEnemyManager* mEnemyManager;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UBehaviorTree* BehaviorTreeRef;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ABaseEnemy* EnemyRef;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	void OnSpawn(class AEnemyManager* Manager);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnPawn(AEnemySpawnPoint* SpawnBox);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnControllerDestroy();
};
