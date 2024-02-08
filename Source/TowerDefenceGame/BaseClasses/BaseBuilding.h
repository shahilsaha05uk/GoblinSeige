// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnumClass.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingInterface.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingBuildSignature, int, AmmountToDeduct);

UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public AActor, public IBuildingInterface
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
	
	UPROPERTY(meta = (ExposeOnSpawn),EditAnywhere, BlueprintReadWrite, Category = "Private")
	class UDA_BuildingAsset* BuildingAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* ValidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* InvalidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* SelectMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TEnumAsByte<ETraceTypeQuery> BuildingMovementTraceChannel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	FTimerHandle OnSpawnTimeHandler;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bInPlacementMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bIsPlaced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bCanPlace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	bool bIsSelected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Public")
	TEnumAsByte<EBuildingState> BuildingState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingBuildSignature OnBuildingBuildSignature;

	ABaseBuilding();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeBuildingMaterial(EPlacementMaterial MatToAdd);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveBuilding();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build();
	
	virtual ABaseBuilding* OnSelect_Implementation(AActor* NewBuilding) override;
	virtual void Deselect_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingBuilt(int AmmountToDeduct);
};
