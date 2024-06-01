// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FeedbackWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UFeedbackWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txtFeedback;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateFeedback();
	
	
};
