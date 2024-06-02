// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
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
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateDescriptionOn(FBuildingBuyDetails BuildingDetails);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateDescriptionWithUpgrade(class ABaseBuilding* BuildingRef);
};
