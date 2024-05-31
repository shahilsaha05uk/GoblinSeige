// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "BuildingPlacementSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlacementStateUpdateSignature, EPlacementState, State, class APlacementActor*, PlacementActor);

UCLASS()
class TOWERDEFENCEGAME_API UBuildingPlacementSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlacementStateUpdateSignature OnPlacementStateUpdate;
};
