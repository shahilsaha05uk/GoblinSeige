// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "UObject/Interface.h"
#include "PhaseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPhaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IPhaseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Phase Interface")
	void OnPhaseComplete(int Phase);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Phase Interface")
	void OnPhaseLoaded(int LoadedPhase, FPhaseDetails Details);
};
