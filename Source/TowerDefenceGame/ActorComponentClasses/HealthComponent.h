// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdateSignature, float, CurrentHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class TOWERDEFENCEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float mStartingHealth;
	UPROPERTY()
	float mHealth;
public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnHealthUpdateSignature OnHealthUpdated;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value)
	{
		mHealth = Value;
		OnHealthUpdated.Broadcast(mHealth);
	}
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth(){ return mHealth; }
	
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(float Value)
	{
		mHealth += Value;
		OnHealthUpdated.Broadcast(mHealth);
	}
	UFUNCTION(BlueprintCallable)
	void DeductHealth(float DamageValue)
	{
		mHealth-= DamageValue;
		OnHealthUpdated.Broadcast(mHealth);
	}
};
