// Fill out your copyright notice in the Description page of Project Settings.


#include "GameComplete.h"

#include "Components/TextBlock.h"

void UGameComplete::NativeConstruct()
{
	Super::NativeConstruct();

	const FString GameCompleteText = (bWonGame) ? "You Won!" : "You Lost!";

	GameCompleteColor = (bWonGame) ? FLinearColor::Green : FLinearColor::Red;
	txtGameComplete->SetColorAndOpacity(GameCompleteColor);

	txtGameComplete->SetText(FText::FromString(GameCompleteText));
}
