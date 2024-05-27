// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/InterfaceClasses/InteractableInterface.h"
#include "TowerDefenceGame/InterfaceClasses/SoundInterface.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelectedSignature, ABaseBuilding*, Building);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingFullyUpgradedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurretActivateSignature);

UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public AActor, public ISoundInterface, public IInteractableInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> OverlappingActors;

	UPROPERTY()
	FString BuildingDescription;
	UPROPERTY()
	FString BuildingUpgradeDescription;
	UPROPERTY()
	bool bCanUpgrade;

public:

	UPROPERTY(meta = (ExposeOnSpawn), EditAnywhere, BlueprintReadWrite, Category = "Private")
	FBuildingBuyDetails mBuildingDetails;

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
	void InitDummy();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(FBuildingBuyDetails BuildingDetails);
	
	virtual void PlaySound_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildDecisionTaken(EBuildStatus Status);

#pragma region Building STATE

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeBuildingMaterial(EPlacementMaterial MatToAdd);

#pragma endregion
	
#pragma region Upgrading the Building

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Upgrade();

#pragma endregion

#pragma region Building Modification
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncreaseRange();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PostBuild();
#pragma endregion

#pragma region Interactable Interface methods
	virtual void Interact_Implementation() override;
	virtual void Disassociate_Implementation() override;
	virtual EInteractableType GetInteractableType_Implementation() override { return BUILDING; }
#pragma endregion
};
