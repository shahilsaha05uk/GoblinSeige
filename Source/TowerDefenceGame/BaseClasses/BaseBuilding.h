// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnumClass.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingSpawnSignature);


UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class USceneComponent* RootComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UDecalComponent* DecalComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UWidgetComponent* WidgetComp;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingSpawnSignature OnBuildingSpawnSignature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* ValidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* InvalidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* SelectMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bInPlacementMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bCanPlace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bIsSelected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	TEnumAsByte<EBuildingState> BuildingState;

	ABaseBuilding(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingSpawn();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingMaterial(EPlacementMaterial MatToAdd);
};
