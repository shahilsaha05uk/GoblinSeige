// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "GameFramework/HUD.h"
#include "TowerDefenceGame/InterfaceClasses/HUDInterface.h"
#include "GameHUD.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnUIHoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCursorHoveredSignature);

UCLASS()
class TOWERDEFENCEGAME_API AGameHUD : public AHUD, public IHUDInterface
{
	GENERATED_BODY()

private:
	TMap<EWidgetType, UBaseWidget*> mWidgetInstanceMap;

	UFUNCTION(BlueprintCallable)
	void UpdateInstanceMap(EWidgetType Type, UBaseWidget* NewWidget);

public:

	AGameHUD();

	virtual void BeginPlay() override;

	UPROPERTY()
	FOnUIHoveredSignature OnUIHoveredSignature;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool OnUIHovered();

	virtual bool isCursorHovering_Implementation() override;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCursorHoveredSignature OnCursorHovered;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Privates")
	TMap<TEnumAsByte<EWidgetType>, TSubclassOf<UBaseWidget>> mWidgetClassMap;
	
	virtual UBaseWidget* WidgetInitialiser_Implementation(EWidgetType Type, AInputController* ControllerRef);
	virtual void DestroyWidget_Implementation(EWidgetType Type);
	virtual void HideWidget_Implementation(EWidgetType WidgetToHide) override;
	virtual UBaseWidget* GetWidgetReference_Implementation(EWidgetType Type) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "GetWidget"))
	UBaseWidget* Blueprint_GetWidget(EWidgetType Type);

	// template methods
	template <typename T>
	T* GetWidget(EWidgetType Type, bool bCasted = false)
	{
		if(!mWidgetInstanceMap.Contains(Type))
		{
			UE_LOG(LogTemp, Warning, TEXT("No instance available of this widget type"));
			return nullptr;
		}

		return (bCasted)? Cast<T>(mWidgetInstanceMap[Type]) : mWidgetInstanceMap[Type];
	};

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPrepareForPhaseChange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPhaseChangeComplete();

};

