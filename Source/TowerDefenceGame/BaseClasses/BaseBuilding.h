// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/EnumClass.h"
#include "TowerDefenceGame/InterfaceClasses/BuildingInterface.h"
#include "TowerDefenceGame/InterfaceClasses/SoundInterface.h"
#include "TowerDefenceGame/UIClasses/widgets/BuildingUI.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelectedSignature, ABaseBuilding*, Building);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingFullyUpgradedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurretActivateSignature);

UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public AActor, public IBuildingInterface, public ISoundInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> OverlappingActors;

	UFUNCTION()
	void UpdateDescription();

	UPROPERTY()
	FString BuildingDescription;
	UPROPERTY()
	FString BuildingUpgradeDescription;
	UPROPERTY()
	bool bCanUpgrade;

public:

	UPROPERTY(meta = (ExposeOnSpawn), EditAnywhere, BlueprintReadWrite, Category = "Private")
	FBuildingDetails BuildingDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	int BuildingCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	TEnumAsByte<EBuildingState> BuildingState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TEnumAsByte<ETraceTypeQuery> BuildingMovementTraceChannel;
	
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
	class USoundBase* ProjectileSound;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FTimerHandle OnSpawnTimeHandler;

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
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingFullyUpgradedSignature OnBuildingFullyUpgradedSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTurretActivateSignature OnTurretActivateSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingSelectedSignature OnBuildingSelectedSignature;
	
	ABaseBuilding();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(UDA_BuildingAsset* asset);
	
	virtual FBuildingStats GetBuildingStats_Implementation() override {return FBuildingStats();}

	virtual EBuildingState GetCurrentBuildingState_Implementation() override {return BuildingState;}

	virtual void PlaySound_Implementation() override;
	
#pragma region Building STATE

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeBuildingMaterial(EPlacementMaterial MatToAdd);

#pragma endregion
	
#pragma region Upgrading the Building

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Upgrade();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanUpgrade() { return bCanUpgrade; }

#pragma endregion

#pragma region Building Modification

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncreaseRange();
	
	virtual void Select_Implementation(int OwnerCurrentBalance) override;
	virtual void Deselect_Implementation() override;
	virtual void Move_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSelect();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDeselect();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMove();
	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveBuilding();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PostBuild();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetUpgradeCost();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetBuildingDescription() {return BuildingDescription;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetBuildingUpgradeDescription() {return BuildingUpgradeDescription;}
	#pragma endregion

};
