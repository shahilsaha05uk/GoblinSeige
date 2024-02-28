// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInterface.h"


void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentBalance = StartingBalance;
}

int UCurrencyComponent::GetCurrentBalance()
{
	return CurrentBalance;
}

void UCurrencyComponent::AddMoney(int Amount)
{
	CurrentBalance += Amount;
}

void UCurrencyComponent::SubtractMoney(int Amount)
{
	CurrentBalance -= Amount;
}
