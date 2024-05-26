// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "BuildingSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlacementActorSelectedSignature, class APlacementActor*, PlacementActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildOnPlacementActorSignature);



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingBoughtSignature, const FString&, BuildingID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingRequestedForBuySignature, const FString&, BuildingID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildRequestSignature, EBuildStatus, Status);

UCLASS()
class TOWERDEFENCEGAME_API UBuildingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// This delegate is triggered when the player selects a Placement Actor
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlacementActorSelectedSignature OnPlacementActorSelected;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildOnPlacementActorSignature OnBuildOnPlacementActor;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingRequestedForBuySignature OnBuildingRequestedForBuy;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingBoughtSignature OnBuildingBought;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildRequestSignature OnBuildDecisionTaken;

	UFUNCTION(BlueprintCallable)
	void Trigger_OnBuildingRequestedForBuy(const FString& BuildingID);
	UFUNCTION(BlueprintCallable)
	void Trigger_OnBuildingBought(const FString& BuildingID);
	UFUNCTION(BlueprintCallable)
	void Trigger_OnBuildDecisionTaken(EBuildStatus Status);

	UFUNCTION(BlueprintCallable)
	void Trigger_OnPlacementActorSelected(class APlacementActor* PlacementActor);
	UFUNCTION(BlueprintCallable)
	void Trigger_OnBuildOnPlacement();
};
