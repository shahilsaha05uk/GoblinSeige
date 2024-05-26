// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerUI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UTowerUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnConfirmPlacement;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UButton* btnAbortPlacement;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnConfirmPlacement();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAbortPlacement();
};
