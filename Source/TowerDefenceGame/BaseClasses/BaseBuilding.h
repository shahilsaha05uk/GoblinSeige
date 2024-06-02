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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDecisionMadeSignature, bool, HasConfirmed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingDestructionSignature);

UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public APawn, public IInteractableInterface
{
	GENERATED_BODY()

public:

#pragma region Components

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UStaticMeshComponent* mStaticMeshSelectedComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UUpgradeComponent* mUpgradeComp;

#pragma endregion

#pragma region Delegates

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingDecisionMadeSignature OnBuildingDecisionMade;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingFullyUpgradedSignature OnBuildingFullyUpgradedSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingSelectedSignature OnBuildingSelectedSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingDestructionSignature OnBuildingDestructed;

#pragma endregion

#pragma region Privates
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Private")
	class UDA_UpgradeAsset* UpgradeAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	FBuildingStats BuildingStats;

	UPROPERTY(EditDefaultsOnly, meta = (SliderExponent=1.0, ClampMin=0, ClampMax=100, ToolTip="Set it as percentage"))
	float DeductionPercentage;

	UPROPERTY(BlueprintReadOnly)
	class UResourceSubsystem* mResourceSubsystem;
	UPROPERTY(BlueprintReadOnly)
	FBuildingBuyDetails mBuildingDetails;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBuildingState> BuildingState;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsPlaced;
	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected;

	UPROPERTY(BlueprintReadOnly)
	FString BuildingID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> OverlappingActors;

	UPROPERTY(BlueprintReadOnly)
	FString BuildingDescription;

	UPROPERTY(BlueprintReadOnly)
	FString BuildingUpgradeDescription;
	
	UPROPERTY(BlueprintReadOnly)
	bool bCanUpgrade;

	UPROPERTY(BlueprintReadOnly)
	class APlacementActor* mPlacement;


#pragma endregion

#pragma region Methods

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(FBuildingBuyDetails BuildingDetails, APlacementActor* PlacementActor);

#pragma region Building STATE
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingDecisionTaken(bool HasConfirmed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);

#pragma endregion
	
#pragma region Build
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestructBuilding();

#pragma endregion
	
#pragma region Upgrading the Building

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Upgrade(FUpgradeDetails Details);

#pragma endregion

#pragma region Interactable Interface methods
	virtual void Interact_Implementation() override;
	virtual void Disassociate_Implementation() override;
#pragma endregion

#pragma endregion
	
	ABaseBuilding();
	
	virtual void BeginPlay() override;
	
};
