// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "PlayerHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpgradeButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveButtonClicked);

UCLASS()
class TOWERDEFENCEGAME_API UPlayerHUD : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* root;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnUpgrade;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnMove;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpgradeButtonClicked OnUpgradeButtonClickedSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMoveButtonClicked OnMoveButtonClickedSignature;
	
	UPROPERTY(BlueprintReadWrite)
	class ATowerDefenceGameGameModeBase* gameMode;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void WidgetToggler(ESideMenuSwitcher menu, bool isUpgradeAvailable);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWaveStart();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateMoney(int CurrentBalance);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateWave(int WaveNumber);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building Settings Menu")
	void OnUpgradeButtonClick();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building Settings Menu")
	void OnMoveButtonClick();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnBuildingSettingsMenuOpen();

};
