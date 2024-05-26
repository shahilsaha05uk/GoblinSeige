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
	/*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UVerticalBox* vbBuildingSettings;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UWidgetSwitcher* wsMenuSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UBorder* root;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UOverlay* ol_Prompter;
	
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UButton* btnUpgrade;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UButton* btnMove;
	*/
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UButton* btnWaveStart;


#pragma endregion
	
#pragma region Properties
	/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	ABaseBuilding* BuildingRef;
	*/
	
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

	/*
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void WidgetToggler(class ABaseBuilding* Building);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building Settings Menu")
	void OnUpgradeButtonClick();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building Settings Menu")
	void OnMoveButtonClick();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenBuildingSettingsUI(ABaseBuilding* Building);
	*/
	
	// On Events Triggered methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveStart();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleShop(bool Value);
};


