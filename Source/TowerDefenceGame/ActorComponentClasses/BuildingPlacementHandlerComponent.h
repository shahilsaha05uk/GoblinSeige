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

	UFUNCTION(BlueprintCallable)
	void HandleInteraction();
	/*
	UFUNCTION(BlueprintCallable)
	void OnPlacementSelected(APlacementActor* PlacementActor);
	UFUNCTION(BlueprintCallable)
	void SpawnDummyBuilding(const FString& BuildingID);
	UFUNCTION(BlueprintCallable)
	void OnBuildingDecisionTaken(EBuildStatus Status);

private:
	UFUNCTION()
	void HandleBuildingInteraction(AActor* HitActor);
	UFUNCTION()
	void HandlePlacementInteraction(AActor* HitActor);
	UFUNCTION()
	void CallDisassociate(AActor* Target);
	UFUNCTION()
	void CallInteract(AActor* Target);


	UFUNCTION(BlueprintCallable)
	void OnPlacementUpdated(EPlacementState State, APlacementActor* PlacementActor);

private:
	UFUNCTION()
	void DeselectLastSelectedActor();
	UFUNCTION()
	void DeselectLastPlacement();
	*/

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool GetHit(FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void SpawnDummyBuilding(const FString& BuildingID);

};
