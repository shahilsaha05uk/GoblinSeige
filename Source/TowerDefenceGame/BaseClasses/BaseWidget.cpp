// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

#include "TowerDefenceGame/GameHUD.h"

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(HudRef) HudRef->OnUIHoveredSignature.BindUFunction(this, FName("OnUIHovered"));
}


bool UBaseWidget::OnUIHovered_Implementation()
{
	return bIsInsideUI;
}

void UBaseWidget::CloseWidget_Implementation()
{
	
}

