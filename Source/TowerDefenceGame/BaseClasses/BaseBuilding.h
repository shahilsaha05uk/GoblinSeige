// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/InterfaceClasses/InteractableInterface.h"
#include "TowerDefenceGame/InterfaceClasses/SoundInterface.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "BaseBuilding.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingecisionMadeSignature, bool, HasConfirmed);
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

	// this is called when decision is made on the building whether they will be placed on the map or not
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingecisionMadeSignature OnBuildingDecisionMade;

	// This is called when the building is set to be destructed
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingDestructionSignature OnBuildingDestructed;

#pragma endregion

#pragma region Privates
	
	UPROPERTY(BlueprintReadOnly)
	class UResourceSubsystem* mResourceSubsystem;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Private")
	class UDA_UpgradeAsset* UpgradeAsset;

	UPROPERTY(BlueprintReadOnly)
	class APlacementActor* mPlacement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	FBuildingStats BuildingStats;

	UPROPERTY(BlueprintReadOnly)
	FBuildingBuyDetails mBuildingDetails;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EBuildingState> BuildingState;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsPlaced;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected;

	UPROPERTY(BlueprintReadOnly)
	bool bCanUpgrade;

	UPROPERTY(BlueprintReadOnly)
	FString BuildingID;
	
	UPROPERTY(BlueprintReadOnly)
	FString BuildingDescription;

	UPROPERTY(BlueprintReadOnly)
	FString BuildingUpgradeDescription;
	
	UPROPERTY(EditDefaultsOnly, meta = (SliderExponent=1.0, ClampMin=0, ClampMax=100, ToolTip="Set it as percentage"))
	float DeductionPercentage;


#pragma endregion

#pragma region Methods

	ABaseBuilding();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(FBuildingBuyDetails BuildingDetails, APlacementActor* PlacementActor);

#pragma region Building STATE
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingDecisionTaken(bool HasConfirmed);
#pragma endregion
	
#pragma region Destruction
	
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
	
};
