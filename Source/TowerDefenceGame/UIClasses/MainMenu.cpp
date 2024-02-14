// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	btnNewGame->OnClicked.AddDynamic(this, &UMainMenu::OnNewGameClicked);
	btnSettings->OnClicked.AddDynamic(this, &UMainMenu::OnSettingsClicked);
	btnInstructions->OnClicked.AddDynamic(this, &UMainMenu::OnInstructionsClicked);
	btnQuit->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);
}

void UMainMenu::OnNewGameClicked_Implementation()
{
}

void UMainMenu::OnSettingsClicked_Implementation()
{
}

void UMainMenu::OnInstructionsClicked_Implementation()
{
}

void UMainMenu::OnQuitClicked_Implementation()
{
}
