// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructClass.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FBuildingStats
{
	GENERATED_BODY()

public:

	FBuildingStats(): AttackDamage(0), AttackRange(0), AttackSpeed(0), LaunchSpeed(0), DamageRadius(0)
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float LaunchSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float DamageRadius;
	
};













UCLASS()
class TOWERDEFENCEGAME_API UStructClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	
	
};
