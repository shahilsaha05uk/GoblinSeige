// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerDefenceGame/Actors/PlacementActor.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "BuildingPlacementHandlerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENCEGAME_API UBuildingPlacementHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	// Temps
	UPROPERTY()
	AActor* mCurrentHitActor;
	UPROPERTY()
	class ABaseBuilding* tempBuilding;

	// This stores the reference to the Building Asset
	UPROPERTY(EditDefaultsOnly)
	UDA_BuildingAsset* DA_BuildingAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Private | Building Properties")
	TEnumAsByte<ETraceTypeQuery> InteractableTraceChannel;

	UPROPERTY()
	class UBuildingPlacementSubsystem* mBuildingPlacementSubsystem;
	UPROPERTY()
	class UBuildingSubsystem* mBuildingSubsystem;
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildDecisionTaken(EBuildStatus Status);
	UFUNCTION(BlueprintCallable)
	void HandleInteraction();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool GetHit(FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(const FString& BuildingID);
};
