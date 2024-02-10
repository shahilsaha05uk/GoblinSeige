// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/BaseBuilding.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ATurret : public ABaseBuilding
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	AActor* ClosestTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	AActor* CurrentTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	TArray<AActor*> Targets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	bool bAttacking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Turret Properties")
	float AttackSpeed;



public:
	ATurret();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncreaseRange();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FindTarget();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IdentifyTarget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnNoTargetInRange();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();
};
