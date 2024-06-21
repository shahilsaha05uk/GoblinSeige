// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructClass.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FPhaseDetails
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int TargetsToDestroy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasCutscene;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int TotalMoneyToAddBack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UMediaSource* MediaSource;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> LevelMap;

	FPhaseDetails(): TargetsToDestroy(0), bHasCutscene(false), TotalMoneyToAddBack(10), MediaSource(nullptr)
	{
	}
};

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
struct FProjectileDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Radial")
	float InitialLaunchSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Radial")
	float MaxLaunchSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Radial")
	float ProjectileAccelaration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsRadialProjectile;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float mRadiusSize;
	

	FProjectileDetails(): InitialLaunchSpeed(-1), MaxLaunchSpeed(-1), ProjectileAccelaration(-1), mRadiusSize(-1)
	{
	}
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
	class UDA_UpgradeAsset* UpgradeAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Trajectory Projectile")
	bool bIsTrajectoryTower;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Trajectory Projectile")
	FProjectileDetails ProjectileStats;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Trajectory Projectile")
	class TSubclassOf<class AProjectile> mProjectileClass;


	FBuildingBuyDetails(): BuildingCost(0), BuildingImage(nullptr), mBuildingNiagara(nullptr), UpgradeAsset(nullptr),
	                       bIsTrajectoryTower(false)
	{
	}
};


USTRUCT(Blueprintable, BlueprintType)
struct FUpgradeDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UpgradeID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UpgradeName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UpgradeCost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsTrajectoryProjectile;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FProjectileDetails ProjectileStats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AProjectile> UpgradeProjectile;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FBuildingStats BuildingStats;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsLastUpgrade;

	FUpgradeDetails(): UpgradeID(-1), UpgradeCost(0), UpgradeProjectile(nullptr), bIsTrajectoryProjectile(false),
	                   ProjectileStats(), bIsLastUpgrade(false)
	{
	}
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

	FSoundStruct(): SoundMixRef(nullptr), SoundClassRef(nullptr)
	{
	}
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
