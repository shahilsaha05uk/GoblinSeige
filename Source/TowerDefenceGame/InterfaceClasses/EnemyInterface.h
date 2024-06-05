// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetTarget();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IA_FollowTheSpline(class ASpline* Spline);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IA_EnemyAttack();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool isDead();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TakeRadiamDamage();
};
