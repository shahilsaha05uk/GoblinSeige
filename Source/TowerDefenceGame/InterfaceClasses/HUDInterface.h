// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/EnumClass.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCEGAME_API IHUDInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UBaseWidget* WidgetInitialiser(EWidgetType Type, AInputController* ControllerRef);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyWidget(EWidgetType Type);
	
};
