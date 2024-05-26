// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "ShopMenu.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API UShopMenu : public UBaseWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseWidget> ButtonClass;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDA_BuildingAsset* mBuildingAsset;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UMultiLineEditableTextBox* txtDescription;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupButtons();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnButtonStateUpdate(const FString& BuildingID, EButtonState State);
	UFUNCTION(BlueprintCallable)
	void UpdateDescription(const FString& Description);
};
