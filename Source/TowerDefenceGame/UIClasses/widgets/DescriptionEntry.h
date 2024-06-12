// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptionEntry.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UDescriptionEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtLabel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtCurrent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtNext;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn))
	FText mLabel;
	
	UFUNCTION(BlueprintCallable)
	void ClearFields();
	
	UFUNCTION(BlueprintCallable)
	void UpdateAllFields();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateCurrent(const FText& Current);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta =(Tooltip = "-1 if it is worse, 0 if they are the same and 1 if they are better"))
	void UpdateNext(const FText& Next, int bIsBetterThanCurrent);
};
