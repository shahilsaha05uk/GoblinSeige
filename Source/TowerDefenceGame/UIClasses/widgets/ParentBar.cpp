// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerDefenceGame/ActorComponentClasses/HealthComponent.h"

void UParentBar::UpdateBar(float Value)
{
	const float normVal = Value / 100.0f;
	mBar->SetPercent(normVal);
}

void UParentBar::UpdateTextValue(float Value)
{
	const int IntVal = UKismetMathLibrary::FCeil(Value);
	mTextValue->SetText(FText::AsNumber(IntVal));
}

void UParentBar::Init_Implementation(UHealthComponent* HealthComp)
{
	if(HealthComp)
	{
		HealthComp->OnHealthUpdated.AddDynamic(this, &ThisClass::Update);
	}
}


void UParentBar::Update(float Value)
{
	UpdateBar(Value);
	UpdateTextValue(Value);
}
