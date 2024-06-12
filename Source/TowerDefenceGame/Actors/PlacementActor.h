﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingPlacementInterface.h"
#include "TowerDefenceGame/InterfaceClasses/InteractableInterface.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "PlacementActor.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API APlacementActor : public AActor, public IInteractableInterface, public IBuildingPlacementInterface
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly)
	class TSubclassOf<class ABaseBuilding> BuildingTowerClass;

public:
	UPROPERTY()
	class UBuildingPlacementSubsystem* mPlacementSubsystem;

	UPROPERTY(EditDefaultsOnly)
	class UDA_BuildingAsset* DA_BuildingAsset;
	UPROPERTY()
	FString mBuildingID;
	UPROPERTY()
	ABaseBuilding* mOccupiedBuilding;

	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsOccupied;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EPlacementState> pState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMeshComponent* mStaticMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USphereComponent* mSphereComp;

	APlacementActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TogglePlacement(bool Activate);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingDecisionTaken(bool HasConfirmed);
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateState(EPlacementState State);

#pragma region Interfaces

	virtual void Interact_Implementation() override;
	virtual void Disassociate_Implementation() override;

#pragma endregion

#pragma region Builders

	virtual ABaseBuilding* Build_Implementation(const FString& BuildingID) override;

	UFUNCTION(BlueprintCallable)
	void OnBuildingDestructed();

#pragma endregion

#pragma region Togglers

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleVisibility(bool Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleMaterial(bool Value);

#pragma endregion

#pragma region Phase

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPhaseComplete(int Phase);

#pragma endregion

	
};
