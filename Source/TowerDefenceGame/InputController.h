// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "DataAssetClasses/DA_InputActions.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyMenuOptionClickSignature, class UDA_BuildingAsset*, BuildingAsset);

UCLASS()
class TOWERDEFENCEGAME_API AInputController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UDA_InputActions* DA_Inputs;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	const UInputMappingContext* InputMappingContext;

	AInputController();
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

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
};
