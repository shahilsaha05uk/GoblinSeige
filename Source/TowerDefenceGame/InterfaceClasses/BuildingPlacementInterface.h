// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingPlacementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBuildingPlacementInterface : public UInterface
{
	GENERATED_BODY()
};


class TOWERDEFENCEGAME_API IBuildingPlacementInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ABaseBuilding* Build(const FString& BuildingID);

};
