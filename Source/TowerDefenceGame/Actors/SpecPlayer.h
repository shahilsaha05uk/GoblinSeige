// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/ActorComponentClasses/CurrencyComponent.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInputInterface.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInterface.h"
#include "SpecPlayer.generated.h"




UCLASS()
class TOWERDEFENCEGAME_API ASpecPlayer : public APawn, public IPlayerInputInterface, public IPlayerInterface
{
	GENERATED_BODY()

public:

	ASpecPlayer();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class AInputController* ControllerRef;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class UCurrencyComponent* CurrencyComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	FTimerHandle OnSpawnTimeHandler;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	ABaseBuilding* tempBuilding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	AActor* selectedActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	TEnumAsByte<ETraceTypeQuery> BuildingTraceChannel;

	virtual void Move_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void Look_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void EnableLook_Implementation() override;
	virtual void DisableLook_Implementation() override;
	virtual void LeftMouseActions_Implementation() override;
	virtual void Zoom_Implementation(float Value) override;
	
	virtual void UpgradeSelectedBuilding_Implementation(ABaseBuilding* BuildingToUpgrade, int UpgradeCost) override;
	virtual void MoveSelectedBuilding_Implementation() override;

	virtual void AddMoneyToAccount_Implementation(int Value) override {CurrencyComponent->AddMoney(Value);}
	virtual void RequestCurrencyUpdate_Implementation(int CurrentBalance) override;
	virtual int GetCurrentBalance_Implementation() override {return CurrencyComponent->GetCurrentBalance(); }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnBuilding(class ABaseBuilding* NewBuilding, UDA_BuildingAsset* BuildingAsset);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingSelected(ABaseBuilding* Building);
};
