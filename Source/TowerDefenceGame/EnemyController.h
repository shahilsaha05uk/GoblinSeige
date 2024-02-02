// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemySpawnPoint.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:

	uint32 UniqueID;

	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UBehaviorTree* BehaviorTreeRef;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	uint32 GetID() {return UniqueID;}
	
	UFUNCTION(BlueprintCallable)
	void OnSpawn(class AEnemyManager* Manager);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnPawn(AEnemySpawnPoint* SpawnBox);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPawnSpawnRequest(AEnemySpawnPoint* SpawnBox);

	
};
