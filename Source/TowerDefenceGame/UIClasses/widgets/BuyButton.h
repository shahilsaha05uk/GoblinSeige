// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "BuyButton.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UBuyButton : public UBaseWidget
{
	GENERATED_BODY()

private:

	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Properties")
	class UBorder* ButtonBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Properties")
	class UButton* BuyButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	TMap<TEnumAsByte<EButtonState>, FLinearColor> ButtonColorMap;
	
	UPROPERTY(BlueprintReadOnly)
	FButtonStyle defaultStyle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	FButtonStyle ButtonStyle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	FString BuildingDescription;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties", meta = (ExposeOnSpawn = true))
	class UPlayerHUD* PlayerHUDRef;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class UMultiLineEditableTextBox* txtDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties", meta = (ExposeOnSpawn = true))
	UDA_BuildingAsset* BuildingAsset;

	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnButtonHovered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnButtonUnhovered();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuyButtonClicked();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCurrentBalanceUpdated(int CurrentBalance);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCurrentBalanceLessThanTheBuildingCost(int CurrentBalance) {return (CurrentBalance > BuildingAsset->BuildingCost);}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateButtonState(EButtonState State);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateDescription(bool bSetToDefault = true);
};
