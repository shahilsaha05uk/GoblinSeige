// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurrencyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCEGAME_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	int CurrentBalance;
public:	

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	int GetCurrentBalance();
	
	UFUNCTION(BlueprintCallable)
	void AddMoney(int Amount);

	UFUNCTION(BlueprintCallable)
	void SubtractMoney(int Amount);

	UFUNCTION(BlueprintCallable)
	void RequestHUDUpdate();
};
