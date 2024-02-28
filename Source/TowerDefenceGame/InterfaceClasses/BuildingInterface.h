// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame//SupportClasses/StructClass.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IBuildingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Select(int OwnerCurrentBalance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Deselect();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Move();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EBuildingState GetCurrentBuildingState();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FBuildingStats GetBuildingStats();

};
