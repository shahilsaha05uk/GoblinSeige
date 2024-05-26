// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/InterfaceClasses/InteractableInterface.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "PlacementActor.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API APlacementActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	class UDA_BuildingAsset* DA_BuildingAsset;
	UPROPERTY()
	FString tmpBuildingID;
	UPROPERTY()
	ABaseBuilding* tempBuilding;

	
public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMeshComponent* mStaticMesh;

	APlacementActor();

	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation() override;
	virtual void Disassociate_Implementation() override;
	virtual EInteractableType GetInteractableType_Implementation() override { return PLACEMENT; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BuildDummy(const FString& BuildingID);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build(EBuildStatus Status);

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildOnPlacement();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleVisibility(bool Value);
};
