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

	FBuildingStats(): BaseDamage(0), BaseDamageRadius(0), AttackRange(0), AttackSpeed(0), ProjectileLaunchSpeed(0)
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float BaseDamageRadius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float ProjectileLaunchSpeed;
	
};

USTRUCT(Blueprintable, BlueprintType)
struct FSoundStruct
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sound Properties")
	USoundMix* SoundMixRef;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sound Properties")
	USoundClass* SoundClassRef;
};

USTRUCT(Blueprintable, BlueprintType)
struct FBuildingDetails
{
	GENERATED_BODY()

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
};

// Save Game Structs

USTRUCT(Blueprintable, BlueprintType)
struct FSoundSave
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sound Saves")
	float GameVolume;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sound Saves")
	float MenuVolume;

	FSoundSave(): GameVolume(0), MenuVolume(0)
	{
	}
};


UCLASS()
class TOWERDEFENCEGAME_API UStructClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	
	
};
