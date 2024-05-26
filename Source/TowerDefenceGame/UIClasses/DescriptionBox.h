// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "DescriptionBox.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UDescriptionBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDA_BuildingAsset* mBuildingAsset;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UTextBlock* txtBuildingName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	class UMultiLineEditableTextBox* txtDescription;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateDescription(const FString& BuildingID, EButtonState State);
};
