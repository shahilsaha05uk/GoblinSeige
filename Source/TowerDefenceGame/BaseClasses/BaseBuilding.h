// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnumClass.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingInterface.h"
#include "TowerDefenceGame/UIClasses/widgets/BuildingUI.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingFullyUpgradedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurretActivateSignature);

UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public AActor, public IBuildingInterface
{
	GENERATED_BODY()

private:
	
	
public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class USceneComponent* RootComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UDecalComponent* PlacementDecalComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UDecalComponent* RangeDecalComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class USphereComponent* RangeCollisionComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FTimerHandle OnSpawnTimeHandler;

	UPROPERTY(meta = (ExposeOnSpawn), EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	class UDA_BuildingAsset* BuildingAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Modification")
	class UDA_UpgradeAsset* UpgradeAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	UMaterialInterface* ValidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	UMaterialInterface* InvalidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	UMaterialInterface* SelectMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	bool bInPlacementMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	bool bIsPlaced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	bool bCanPlace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	bool bIsSelected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	TEnumAsByte<EBuildingState> BuildingState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Modification")
	TEnumAsByte<ETraceTypeQuery> BuildingMovementTraceChannel;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingFullyUpgradedSignature OnBuildingFullyUpgradedSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTurretActivateSignature OnTurretActivateSignature;

	ABaseBuilding();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(UDA_BuildingAsset* asset);
	
	virtual FBuildingStats GetBuildingStats_Implementation() override {return FBuildingStats();}
	
#pragma region Building STATE

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeBuildingMaterial(EPlacementMaterial MatToAdd);

#pragma endregion
	
#pragma region Upgrading the Building

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool isUpgradeAvailable();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Upgrade();
	UFUNCTION(BlueprintCallable)
	bool isFullyUpgraded();

#pragma endregion

#pragma region Building Modification

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncreaseRange();
	
	virtual ABaseBuilding* Select_Implementation(AActor* NewBuilding) override;

	virtual void Deselect_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSelect();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDeselect();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveBuilding();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingStats(FBuildingStats stats);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PostBuild();
	#pragma endregion

};
