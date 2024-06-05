// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "ShopMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShopButtonHoverSignature, FBuildingBuyDetails, BuildingDetails);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopButtonUnhoverSignature);

UCLASS()
class TOWERDEFENCEGAME_API UShopMenu : public UBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDA_BuildingAsset* mBuildingAsset;

	UPROPERTY(BlueprintReadWrite, meta=  (ExposeOnSpawn))
	class UPlayerHUD* mHUD;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnShopButtonHoverSignature OnShopButtonHovered;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnShopButtonUnhoverSignature OnShopButtonUnhover;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(class UPlayerHUD* Hud);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupButtons();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnButtonStateUpdate(const FString& BuildingID, EButtonState State);
};
