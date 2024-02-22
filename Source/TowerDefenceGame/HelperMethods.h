// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructClass.h"
#include "HelperMethods.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UHelperMethods : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void GetMouseLocation(APlayerController* Controller, FVector &MouseLocation);

	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void GetMouseTrace(APlayerController* Controller ,ETraceTypeQuery TraceQuery, bool &Value, FHitResult &hit);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	static void CalculateSnappedPosition(FVector HitLocation, float SnapInterval, FVector &SnappedPosition);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	static float GetDotProductBetweenComponentWorldLocationAndActorLocation(USceneComponent* Component, AActor* Actor);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	static FString GetDescription(FBuildingStats stats);
};
