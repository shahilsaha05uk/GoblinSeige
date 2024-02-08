// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInterface.h"


void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentBalance = 500;
	AActor* Owner = GetOwner();
	if(UKismetSystemLibrary::DoesImplementInterface(Owner, UPlayerInterface::StaticClass()))
	{
		IPlayerInterface::Execute_RequestCurrencyUpdate(Owner, CurrentBalance);
	}
}

int UCurrencyComponent::GetCurrentBalance()
{
	return CurrentBalance;
}
