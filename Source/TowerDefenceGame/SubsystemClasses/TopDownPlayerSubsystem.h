// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "TopDownPlayerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeBuildingSignature, int, BuildingID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveBuildingSignature, class ABaseBuilding*, Building);
UCLASS()
class TOWERDEFENCEGAME_API UTopDownPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
};
