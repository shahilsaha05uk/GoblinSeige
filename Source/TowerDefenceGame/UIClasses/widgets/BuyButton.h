// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "BuyButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonStateUpdateSignature, FString, BuildingID, EButtonState, CurrentState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyButtonClickSignature, FString, BuildingID);

UCLASS()
class TOWERDEFENCEGAME_API UBuyButton : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
	class UResourceSubsystem* mResourceSubsystem;

public:
	UPROPERTY(meta =(ExposeOnSpawn = true), BlueprintReadWrite)
	FBuildingBuyDetails mBuildingDetails;
	
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

	// Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnButtonStateUpdateSignature OnButtonStateUpdate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnBuyButtonClickSignature OnBuyButtonClick;

	UFUNCTION(BlueprintCallable)
	void Init();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnButtonHovered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnButtonUnhovered();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuyButtonClicked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateButtonState(EButtonState State);

	// This will update the state of the Button whenever its called
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateButton();

	// Called When the resources get updated
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnResourceUpdated(int CurrentBalance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildRequest();

};
