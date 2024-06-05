// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "GameComplete.generated.h"


UCLASS()
class TOWERDEFENCEGAME_API UGameComplete : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txtGameComplete;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnReturnToMainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnQuit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	FLinearColor GameCompleteColor;
};
