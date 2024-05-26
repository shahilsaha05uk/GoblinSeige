// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class TOWERDEFENCEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor Properties")
	float mHealth;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth(){ return mHealth; }
	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value){ mHealth = Value; }
	
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(float Value) {mHealth += Value; }
	UFUNCTION(BlueprintCallable)
	void DeductHealth(float DamageValue) {mHealth-= DamageValue;}
};
