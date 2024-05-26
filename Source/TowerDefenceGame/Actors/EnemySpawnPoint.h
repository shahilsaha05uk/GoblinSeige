// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintNativeEvent)
	FVector GetRandomPointInsideTheSpawnArea();
	
};
