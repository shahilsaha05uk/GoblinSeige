// Fill out your copyright notice in the Description page of Project Settings.


#include "DescriptionEntry.h"

#include "Components/TextBlock.h"

void UDescriptionEntry::ClearFields()
{
	txtCurrent->SetText(FText::FromString(TEXT("")));
	txtNext->SetText(FText::FromString(TEXT("")));
}

void UDescriptionEntry::ClearNextFields()
{
	txtNext->SetText(FText::FromString(TEXT("")));
}

void UDescriptionEntry::UpdateAllFields()
{
	txtLabel->SetText(mLabel);
}

void UDescriptionEntry::UpdateCurrent_Implementation(const FText& Current)
{
	txtCurrent->SetText(Current);
}

void UDescriptionEntry::UpdateNext_Implementation(const FText& Next, int bIsBetterThanCurrent)
{
	txtNext->SetText(Next);
}