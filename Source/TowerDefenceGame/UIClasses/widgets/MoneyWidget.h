// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "MoneyWidget.generated.h"


UCLASS()
class TOWERDEFENCEGAME_API UMoneyWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtMoney;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateMoney(int Value);
};
