// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	float mBaseDamageValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	float mDamageRadius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	FVector mTargetLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	float mLaunchSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	AActor* mTarget;


	AProjectile();
};

