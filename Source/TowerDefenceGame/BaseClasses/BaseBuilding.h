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

UCLASS()
class TOWERDEFENCEGAME_API ABaseBuilding : public APawn, public IInteractableInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FString BuildingID;
	UPROPERTY()
	class UDA_UpgradeAsset* UpgradeAsset;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> OverlappingActors;

	UPROPERTY()
	FString BuildingDescription;
	UPROPERTY()
	FString BuildingUpgradeDescription;
	UPROPERTY()
	bool bCanUpgrade;
	UPROPERTY()
	FBuildingBuyDetails mBuildingDetails;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FBuildingStats BuildingStats;

	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UStaticMeshComponent* mStaticMeshSelectedComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private")
	TEnumAsByte<EBuildingState> BuildingState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Modification")
	bool bIsSelected;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingFullyUpgradedSignature OnBuildingFullyUpgradedSignature;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuildingSelectedSignature OnBuildingSelectedSignature;
	
	ABaseBuilding();


	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(FBuildingBuyDetails BuildingDetails);
	
#pragma region Building STATE
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingDecisionTaken(EBuildStatus Status);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingState(EBuildingState State);

#pragma endregion
	
#pragma region Upgrading the Building

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Upgrade();

#pragma endregion

#pragma region Interactable Interface methods
	virtual void Interact_Implementation() override;
	virtual void Disassociate_Implementation() override;
#pragma endregion
};
