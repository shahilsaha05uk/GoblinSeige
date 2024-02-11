// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "TowerDefenceGameGameModeBase.h"
#include "DataAssetClasses/DA_InputActions.h"
#include "GameFramework/PlayerController.h"
#include "InterfaceClasses/ControllerInterface.h"
#include "InputController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyMenuOptionClickSignature, class UDA_BuildingAsset*, BuildingAsset);

UCLASS()
class TOWERDEFENCEGAME_API AInputController : public APlayerController, public IControllerInterface
{
	GENERATED_BODY()

private:

	bool bIsOverUI;

	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UDA_InputActions* DA_Inputs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ASpecPlayer* SpecPawn;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	const UInputMappingContext* InputMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class AGameHUD* GameHUD;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class UPlayerHUD* PlayerHUD;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	ATowerDefenceGameGameModeBase* GameMode;


	AInputController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetIsOverUI_Implementation(bool b) override { bIsOverUI = b;}
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateCurrency(int CurrentBalance);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWaveComplete(int WaveNumber);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnBuyMenuOptionClickSignature OnBuyMenuOptionClickSignature;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuyOptionClicked(UDA_BuildingAsset* BuildingAsset);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Move(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Look(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EnableLook(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisableLook(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LeftMouseActions();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Zoom(const FInputActionValue& InputActionValue);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SideWidgetToggler(ESideMenuSwitcher menu, bool isUpgradeAvailable  = true);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingBuilt(int CurrentBalance);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpgradeButtonClick();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMoveButtonClick();

};
