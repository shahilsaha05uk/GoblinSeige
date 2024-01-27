// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/InputController.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private")
	AInputController* Controller;
};
