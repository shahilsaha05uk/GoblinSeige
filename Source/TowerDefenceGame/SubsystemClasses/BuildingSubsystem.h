// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BuildingSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingBoughtSignature, const FString&, BuildingID);

UCLASS()
class TOWERDEFENCEGAME_API UBuildingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingBoughtSignature OnBuildingBought;

	UFUNCTION(BlueprintCallable)
	void Trigger_OnBuildingBought(const FString& BuildingID);
};
