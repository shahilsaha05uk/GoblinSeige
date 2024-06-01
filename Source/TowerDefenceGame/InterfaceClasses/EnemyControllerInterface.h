// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEnemyControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IEnemyControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnemyMove(FVector TargetLocation);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnemyAttack();
};
