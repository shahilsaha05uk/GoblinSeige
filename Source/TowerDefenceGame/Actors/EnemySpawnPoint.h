// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"
#include "TowerDefenceGame/InterfaceClasses/SpawnPointInterface.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AEnemySpawnPoint : public AActor, public ISpawnPointInterface
{
	GENERATED_BODY()

private:

	UPROPERTY()
	class UGameSubsystem* mGameSubsystem;
public:
	virtual void BeginPlay() override;
	
	virtual FVector GetRandomPointWithinTheBounds_Implementation() override;
};
