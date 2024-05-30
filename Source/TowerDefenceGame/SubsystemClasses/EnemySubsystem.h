// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyOnDeadSignature, class AEnemyController*, ControllerRef);
UCLASS()
class TOWERDEFENCEGAME_API UEnemySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<class AEnemySpawnPoint*> mSpawnPoints;

	UPROPERTY()
	int EnemySpawnPointCount;
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEnemyOnDeadSignature OnEnemyDead;
	// All the spawn points registers themselves with the subsystem at the start of the play 
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnPoint(class AEnemySpawnPoint* SpawnPoint);
	UFUNCTION(BlueprintCallable)
	void DeRegisterSpawnPoint();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class AEnemySpawnPoint* GetRandomEnemySpawnPoint();
};
