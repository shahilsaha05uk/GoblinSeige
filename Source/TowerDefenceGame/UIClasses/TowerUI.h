// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/Actors/PlacementActor.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerUI.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecisionMadeSignature, bool, HasConfirmed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeRequestedSignature, const FUpgradeDetails&, UpgradeDetails);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyRequestedSignature);

UCLASS()
class TOWERDEFENCEGAME_API UTowerUI : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ATower* mTowerRef;

	
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnConfirmPlacement;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnAbortPlacement;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnUpgradeBuilding;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnDestroyBuilding;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeckType> ActiveDeck;
	
	UPROPERTY(BlueprintReadOnly)
	int mBuildingCost;
	

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnUpgradeRequestedSignature OnUpgradeRequested;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDecisionMadeSignature OnDecisionMade;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(int Cost, class ATower* Tower);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleWidgetSwitcher(EDeckType Type);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateUI();


#pragma region Confirm Methods

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnConfirmPlacement();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAbortPlacement();

#pragma endregion

#pragma region Upgrade Methods

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpgradeBuilding();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDestroyBuilding();
#pragma endregion
	
};
