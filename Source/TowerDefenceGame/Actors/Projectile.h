// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileJobCompleteSignature, class AProjectile*, Projectile);


UCLASS()
class TOWERDEFENCEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()

private:

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnProjectileJobCompleteSignature OnProjectileJobComplete;

	
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateProjectile(AActor* Target);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DeactivateProjectile();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnMuzzle();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnProjectile();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopProjectile();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetProjectileTemplateToEmpty();
};

