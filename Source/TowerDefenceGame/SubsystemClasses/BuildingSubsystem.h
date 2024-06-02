// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "BuildingSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingRequestedForBuySignature, const FString&, BuildingID);
UCLASS()
class TOWERDEFENCEGAME_API UBuildingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingRequestedForBuySignature OnBuildingRequestedForBuy;
};
