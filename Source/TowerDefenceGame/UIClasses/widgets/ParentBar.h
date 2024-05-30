// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParentBar.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UParentBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, meta = (ExposeOnSpawn))
	class UProgressBar* mBar;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* mTextValue;

	UFUNCTION(BlueprintCallable)
	void UpdateBar(float Value);
	UFUNCTION(BlueprintCallable)
	void UpdateTextValue(float Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(class UHealthComponent* HealthComp);
	
	UFUNCTION(BlueprintCallable)
	void Update(float Value);
};
