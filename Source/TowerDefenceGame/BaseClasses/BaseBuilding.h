// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnumClass.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingInterface.h"
#include "TowerDefenceGame/UIClasses/widgets/BuildingUI.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingBuildSignature, int, AmmountToDeduct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingFullyUpgradedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurretActivateSignature);
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
	class UDecalComponent* PlacementDecalComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class UDecalComponent* RangeDecalComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	class USphereComponent* RangeCollisionComp;
	
	UPROPERTY(meta = (ExposeOnSpawn),EditAnywhere, BlueprintReadWrite, Category = "Private")
	class UDA_BuildingAsset* BuildingAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* ValidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* InvalidMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	UMaterialInterface* SelectMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Upgrade Properties")
	class UDA_UpgradeAsset* UpgradeAsset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TEnumAsByte<ETraceTypeQuery> BuildingMovementTraceChannel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UBuildingUI* buildingUI;
	
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
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingFullyUpgradedSignature OnBuildingFullyUpgradedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTurretActivateSignature OnTurretActivateSignature;
	ABaseBuilding();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool isUpgradeAvailable();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Upgrade();
	UFUNCTION(BlueprintCallable)
	bool isFullyUpgraded();
	
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
