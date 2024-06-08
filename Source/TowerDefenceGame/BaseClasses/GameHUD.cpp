// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"

AGameHUD::AGameHUD()
{
	
}


void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->InitialiseHud(this);
	}
}

bool AGameHUD::OnUIHovered_Implementation()
{
	if(OnUIHoveredSignature.IsBound()) return OnUIHoveredSignature.Execute();

	return false;
}

void AGameHUD::UpdateInstanceMap(EWidgetType Type, UBaseWidget* NewWidget)
{
	if(mWidgetInstanceMap.Contains(Type))
	{
		return;
	}
	mWidgetInstanceMap.Add(Type, NewWidget);
}

void AGameHUD::DestroyWidget_Implementation(EWidgetType Type)
{
	if(mWidgetInstanceMap.Contains(Type))
	{
		mWidgetInstanceMap[Type]->RemoveFromParent();
		mWidgetInstanceMap.Remove(Type);
	}
}

void AGameHUD::HideWidget_Implementation(EWidgetType WidgetToHide)
{
	if(mWidgetInstanceMap.Contains(WidgetToHide))
		mWidgetInstanceMap[WidgetToHide]->SetVisibility(ESlateVisibility::Hidden);
}

UBaseWidget* AGameHUD::GetWidgetReference_Implementation(EWidgetType Type)
{
	return (mWidgetInstanceMap.Contains(Type))? mWidgetInstanceMap[Type] : nullptr;
}

bool AGameHUD::isCursorHovering_Implementation()
{
	return OnUIHovered();
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