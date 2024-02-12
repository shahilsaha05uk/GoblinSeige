// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInterface.h"


void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentBalance = StartingBalance;
	RequestHUDUpdate();

}

int UCurrencyComponent::GetCurrentBalance()
{
	return CurrentBalance;
}

void UCurrencyComponent::AddMoney(int Amount)
{
	CurrentBalance += Amount;

	RequestHUDUpdate();
}

void UCurrencyComponent::SubtractMoney(int Amount)
{
	CurrentBalance -= Amount;

	RequestHUDUpdate();
}

void UCurrencyComponent::RequestHUDUpdate()
{
	AActor* Owner = GetOwner();
	if(UKismetSystemLibrary::DoesImplementInterface(Owner, UPlayerInterface::StaticClass()))
	{
		IPlayerInterface::Execute_RequestCurrencyUpdate(Owner, CurrentBalance);
	}

}
