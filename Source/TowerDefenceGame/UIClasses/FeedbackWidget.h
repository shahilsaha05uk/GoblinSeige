// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FeedbackWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFeedbackSystemEnableSignature);

UCLASS()
class TOWERDEFENCEGAME_API UFeedbackWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	class UTextBlock* txtFeedback;

	UPROPERTY(BlueprintReadOnly)
	class UPlayerHUD* mPlayerHUD;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnFeedbackSystemEnableSignature OnFeedbackEnabled;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(class UPlayerHUD* HudRef);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateFeedback(const FString& StrToDisplay);

	UFUNCTION(BlueprintCallable)
	void OnWaveStarted(int Wave);
	UFUNCTION()
	void OnWaveEnded(int Wave);
	UFUNCTION(BlueprintCallable)
	void OnDoorBroken();
};
