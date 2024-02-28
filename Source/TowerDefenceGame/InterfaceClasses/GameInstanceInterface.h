// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "UObject/Interface.h"
#include "GameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IGameInstanceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TravelToMap(ELevelToTravel LevelToTravel);
};
