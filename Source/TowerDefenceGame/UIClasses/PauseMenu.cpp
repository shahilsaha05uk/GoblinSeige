// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "Components/Button.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	btnResume->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);
	btnReturnToMainMenu->OnClicked.AddDynamic(this, &UPauseMenu::OnReturnToMainMenuClicked);
	btnQuit->OnClicked.AddDynamic(this, &UPauseMenu::OnQuitClicked);
}

void UPauseMenu::OnResumeClicked_Implementation()
{
}

void UPauseMenu::OnReturnToMainMenuClicked_Implementation()
{
}

void UPauseMenu::OnQuitClicked_Implementation()
{
}
