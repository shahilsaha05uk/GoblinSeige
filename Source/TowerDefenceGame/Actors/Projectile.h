// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "Projectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileJobCompleteSignature, class AProjectile*, Projectile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageDealtSignature);


UCLASS()
class TOWERDEFENCEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()

private:

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnProjectileJobCompleteSignature OnProjectileJobComplete;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDamageDealtSignature OnDamageDealt;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Private | Projectile Properties")
	float mLaunchSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	float mDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	FVector mTargetLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "Private | Projectile Properties")
	AActor* mTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Projectile Properties")
	class UNiagaraSystem* mProjectileMuzzleAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Projectile Properties")
	class UNiagaraSystem* mProjectileAsset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Projectile Properties")
	class UNiagaraSystem* mProjectileHitAsset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class USoundBase* ProjectileSound;


	AProjectile();

	UFUNCTION()
	void Init(FOnProjectileUpgradeSignature OnUpgradeSignature);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateProjectile(AActor* Target, float MinSpeed = -1, float MaxSpeed = -1);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DeactivateProjectile();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUpgrade(FProjectileDetails ProjectileDetails);

};

