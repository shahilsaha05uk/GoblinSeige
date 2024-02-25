// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "../EnumClass.h"
#include "PlayerHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpgradeButtonClickedSignature, class ABaseBuilding*, BuildingToUpgrade, int, UpgradeCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveButtonClickedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentBalanceUpdatedSignature, int, CurrentBalance);



UCLASS()
class TOWERDEFENCEGAME_API UPlayerHUD : public UBaseWidget
{
	GENERATED_BODY()

private:

	void UpdateIntValues(EHudValue ValueType, int Value);

	void UpdateStringValues(EHudValue ValueType, FString Value);

	void GetStringForBuilding(ABaseBuilding* Building, FLinearColor &colorToAdd, FString &txtToAdd);


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	TArray<class UDA_BuildingAsset*> BuildingAssetArray;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	int mCurrentBalance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	ABaseBuilding* BuildingRef;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	FString NextUpgradeStats;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtWave;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtMoney;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtMoneyUpgradeMenu;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UMultiLineEditableTextBox* txtDescriptionUpgradeMenu;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtBuildingNameUpgradeMenu;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UVerticalBox* vbShop;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UVerticalBox* vbBuildingSettings;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UWidgetSwitcher* wsMenuSwitcher;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UBorder* root;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UMultiLineEditableTextBox* txtDescription;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UButton* btnWaveStart;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UButton* btnUpgrade;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UButton* btnMove;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UOverlay* ol_Prompter;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpgradeButtonClickedSignature OnUpgradeButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMoveButtonClickedSignature OnMoveButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCurrentBalanceUpdatedSignature OnCurrentBalanceUpdated;
	
	
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UBaseWidget> PrompterWidgetClass;
	
	UPROPERTY(BlueprintReadWrite)
	class ATowerDefenceGameGameModeBase* gameMode;

	virtual void NativeConstruct() override;

	template <typename T>
	void Updater(EHudValue ValueToUpdate, T Value)
	{
		if constexpr(std::is_same_v<T, int>) UpdateIntValues(ValueToUpdate, Value);
		if constexpr(std::is_same_v<T, FString>) UpdateStringValues(ValueToUpdate, Value);

		PostWidgetUpdate(ValueToUpdate);
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PostWidgetUpdate(EHudValue ValueType);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void WidgetToggler(class ABaseBuilding* Building);

	// On Events Triggered methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveStart();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveComplete(int WaveNumber);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building Settings Menu")
	void OnUpgradeButtonClick();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building Settings Menu")
	void OnMoveButtonClick();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PopulateBuildingButtons(class UBuyButton* ButtonRef);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BuyMenuSetup();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenBuildingSettingsUI(ABaseBuilding* Building);

};


