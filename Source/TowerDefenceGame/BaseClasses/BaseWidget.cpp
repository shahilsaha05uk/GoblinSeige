// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/GameHUD.h"

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(HudRef) HudRef->OnUIHoveredSignature.BindUFunction(this, FName("OnUIHovered"));
}

void UBaseWidget::OnReturnToMainMenu_Implementation()
{
}

void UBaseWidget::OnQuitGame_Implementation()
{
	TEnumAsByte<EQuitPreference::Type> prefs = {};
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), prefs, false);
}


bool UBaseWidget::OnUIHovered_Implementation()
{
	return bIsInsideUI;
}

void UBaseWidget::CloseWidget_Implementation()
{
	
}

