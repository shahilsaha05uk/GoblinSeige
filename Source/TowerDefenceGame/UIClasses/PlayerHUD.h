// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "PlayerHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpgradeButtonClickedSignature, class ABaseBuilding*, BuildingToUpgrade, int, UpgradeCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveButtonClickedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentBalanceUpdatedSignature, int, CurrentBalance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuyButtonHoveredClickedSignature, FBuildingBuyDetails, BuildingDetails);



UCLASS()
class TOWERDEFENCEGAME_API UPlayerHUD : public UBaseWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
	class UResourceSubsystem* mResourceSubsystem;
	
public:
#pragma region Components
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UShopMenu* mShop;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UDescriptionBox* mDescriptionBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UFeedbackWidget* mFeedbackBox;

#pragma endregion
	
#pragma region Properties
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBuyButtonHoveredClickedSignature OnBuyButtonHovered;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpgradeButtonClickedSignature OnUpgradeButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMoveButtonClickedSignature OnMoveButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCurrentBalanceUpdatedSignature OnCurrentBalanceUpdated;
	
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UBaseWidget> PrompterWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	class UGameSubsystem* mGameSubsystem;

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

#pragma region Shop Bindings

	UFUNCTION(BlueprintCallable, BlueprintCallable)
	void OnShopButtonHovered(FBuildingBuyDetails BuildingDetails);

#pragma endregion

#pragma region Description Bindings

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingInterationBegin(ABaseBuilding* BuildingRef);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingInterationEnd(ABaseBuilding* BuildingRef);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleDescriptionBox(bool Activate);

#pragma endregion

#pragma region Feedback

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnFeedbackRecieved(EFeedbackType Type, const FString& MessageToDisplay);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EnableCutscene();

#pragma endregion
};