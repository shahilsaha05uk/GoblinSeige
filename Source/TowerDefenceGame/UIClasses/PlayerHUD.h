// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "PlayerHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpgradeButtonClickedSignature, class ABaseBuilding*, BuildingToUpgrade, int, UpgradeCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveButtonClickedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentBalanceUpdatedSignature, int, CurrentBalance);



UCLASS()
class TOWERDEFENCEGAME_API UPlayerHUD : public UBaseWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
	class UWaveSubsystem* mWaveSubsystem;
	UPROPERTY()
	class UResourceSubsystem* mResourceSubsystem;
	
public:
#pragma region Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UShopMenu* mShop;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UDescriptionBox* mDescriptionBox;

#pragma endregion
	
#pragma region Properties
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpgradeButtonClickedSignature OnUpgradeButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMoveButtonClickedSignature OnMoveButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCurrentBalanceUpdatedSignature OnCurrentBalanceUpdated;
	
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UBaseWidget> PrompterWidgetClass;
	
#pragma endregion

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleShop(bool Value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnButtonStateUpdate(const FString& String, EButtonState State);

#pragma region Building Methods
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingDecisionTaken(EBuildStatus Status);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRequestForBuildingBuy(const FString& BuildingID);

	UFUNCTION(BlueprintCallable)
	void OnPlacementStateUpdated(EPlacementState State, class APlacementActor* PlacementActor);

#pragma endregion
};