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

	FBuildingStats(): Damage(0), Range(0), RateOfFire(0)
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float Range;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float RateOfFire;
	
};

USTRUCT(Blueprintable, BlueprintType)
struct FBuildingBuyDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	FString ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	FString BuildingName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	int BuildingCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	UTexture2D* BuildingImage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	FBuildingStats BuildingStats;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	class UNiagaraSystem* mBuildingNiagara;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	class TSubclassOf<class AProjectile> mProjectileClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Details")
	class UDA_UpgradeAsset* UpgradeAsset;

};

USTRUCT(Blueprintable, BlueprintType)
struct FUpgradeDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UpgradeID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UpgradeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UpgradeCost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraSystem* UpgradeNiagara;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FBuildingStats BuildingStats;
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
