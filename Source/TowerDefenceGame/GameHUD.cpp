// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"


void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

}

void AGameHUD::UpdateInstanceMap(EWidgetType Type, UBaseWidget* NewWidget)
{
	if(mWidgetInstanceMap.Contains(Type))
	{
		return;
	}
	mWidgetInstanceMap.Add(Type, NewWidget);
}

UBaseWidget* AGameHUD::WidgetInitialiser_Implementation(EWidgetType Type, AInputController* ControllerRef)
{
	if(!mWidgetClassMap.Contains(Type)) return nullptr;
	if(mWidgetInstanceMap.Contains(Type)) return mWidgetInstanceMap[Type];
	
	TSubclassOf<UBaseWidget> WidgetClass = mWidgetClassMap[Type];
	UBaseWidget* NewWidget = CreateWidget<UBaseWidget>(GetWorld(), WidgetClass);
	UpdateInstanceMap(Type, NewWidget);

	return NewWidget;
}

UBaseWidget* AGameHUD::Blueprint_GetWidget(EWidgetType Type)
{
	return GetWidget<UBaseWidget>(Type);
}

template <typename T>
T* AGameHUD::GetWidget(EWidgetType Type, bool bCasted)
{
	if(!mWidgetInstanceMap.Contains(Type))
	{
		UE_LOG(LogTemp, Warning, TEXT("No instance available of this widget type"));
		return nullptr;
	}

	return (bCasted)? Cast<T>(mWidgetInstanceMap[Type]) : mWidgetInstanceMap[Type];
}


