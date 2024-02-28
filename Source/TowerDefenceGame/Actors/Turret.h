// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "Turret.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ATurret : public ABaseBuilding
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	AActor* CurrentTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	TArray<AActor*> Targets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	TSubclassOf<class AProjectile> mProjectileClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool bAttacking;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	FVector TargetLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float RotationTimeInterval;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool bHasRotator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool FireShouldLoop;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool bIsPowerOn;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool RotatorShouldLoop;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool ShouldTurnOnFiring;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Handlers")
	FTimerHandle TurningTimeHandler;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Handlers")
	FTimerHandle FireTimerHandler;

public:

	ATurret();

	virtual void OnSelect_Implementation() override;
	virtual void OnDeselect_Implementation() override;

	virtual void IncreaseRange_Implementation() override;

	virtual void PostBuild_Implementation() override;

	virtual void Upgrade_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnFoundTarget(AActor* FoundTarget);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* FindTarget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PowerOff();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PowerOn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopFire();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnProjectile(TSubclassOf<class AProjectile> ProjectileClass, FVector Location, FRotator Rotation, AActor* Target = nullptr);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LookAtTarget();
	
};
