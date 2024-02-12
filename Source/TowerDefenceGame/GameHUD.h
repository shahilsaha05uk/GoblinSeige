// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "InputController.h"
#include "BaseClasses/BaseWidget.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AGameHUD : public AHUD
{
	GENERATED_BODY()

private:
	TMap<EWidgetType, UBaseWidget*> mWidgetInstanceMap;

public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Privates")
	TMap<TEnumAsByte<EWidgetType>, TSubclassOf<UBaseWidget>> mWidgetClassMap;
	
	UFUNCTION(BlueprintCallable)
	void UpdateInstanceMap(EWidgetType Type, UBaseWidget* NewWidget);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UBaseWidget* WidgetInitialiser(EWidgetType Type, AInputController* ControllerRef);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyWidget(EWidgetType Type);
	
	template <typename T>
	T* GetWidget(EWidgetType Type, bool bCasted = false);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "GetWidget"))
	UBaseWidget* Blueprint_GetWidget(EWidgetType Type);
	
};

