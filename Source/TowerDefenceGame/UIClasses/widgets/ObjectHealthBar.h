// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UObjectHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateValue(float Value);
};
