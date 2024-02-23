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

	FBuildingStats(): AttackDamage(0), AttackRange(0), AttackSpeed(0), ProjectileLaunchSpeed(0), DamageRadius(0)
	{
	}

	FBuildingStats operator+=(const FBuildingStats& otherStats)
	{
		FBuildingStats s;
		s.AttackDamage = AttackDamage + otherStats.AttackDamage;
		s.AttackRange = AttackRange + otherStats.AttackRange;
		s.AttackSpeed = AttackSpeed + otherStats.AttackSpeed;
		s.ProjectileLaunchSpeed = ProjectileLaunchSpeed + otherStats.ProjectileLaunchSpeed;
		s.DamageRadius = DamageRadius + otherStats.DamageRadius;

		return s;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float ProjectileLaunchSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float DamageRadius;
	
};


USTRUCT(Blueprintable, BlueprintType)
struct FBuildingDetails
{
	GENERATED_BODY()

private:
	void OnUpgrade();
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	FString BuildingName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	class UDA_UpgradeAsset* UpgradeAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	int BuildingCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	FBuildingStats BuildingStats;
	
	FBuildingDetails(class UDA_BuildingAsset* BuildingAsset);
	FBuildingDetails();
	void Upgrade()
	{
		OnUpgrade();
	}
};













UCLASS()
class TOWERDEFENCEGAME_API UStructClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	
	
};
