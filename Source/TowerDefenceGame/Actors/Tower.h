// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerDefenceGame/BaseClasses/BaseBuilding.h"
#include "Tower.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileUpgradeSignature, FProjectileDetails, ProjectileDetails);

UENUM(Blueprintable, BlueprintType)
enum ETowerState { Firing, Seek, Idle };

UCLASS()
class TOWERDEFENCEGAME_API ATower : public ABaseBuilding
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	float mSeekRate = 0.5f;

	UPROPERTY()
	FTimerHandle TowerStateTimeHandler;

	UPROPERTY(EditDefaultsOnly)
	int ProjectilePoolCount = 10;

	UPROPERTY(EditDefaultsOnly)
	bool bShouldPool;

	UPROPERTY()
	int PoolCount;

	UPROPERTY()
	int tempPoolCount;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Tower")
	bool bIsInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instanced Tower")
	TSubclassOf<AProjectile> InstancedProjectileClass;


	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ETowerState> TowerState;

	UPROPERTY(BlueprintReadOnly)
	TArray<FUpgradeDetails> mUpgradeDetails;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AProjectile*> mPooledProjectiles;
		
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UWidgetComponent* mTowerWidgetComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UStaticMeshComponent* mStaticMeshComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UNiagaraComponent* mNiagaraComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class USphereComponent* mRangeColliderComp;

	UPROPERTY(BlueprintReadWrite)
	AActor* mTarget;
	
	UPROPERTY(BlueprintReadWrite)
	class UTowerUI* mTowerUI;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnProjectileUpgradeSignature OnProjectileUpgrade;

	ATower();

	virtual void Init_Implementation(FBuildingBuyDetails BuildingDetails, APlacementActor* PlacementActor) override;

	virtual void OnBuildingDecisionTaken_Implementation(bool HasConfirmed) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateRange();
	
	UFUNCTION(BlueprintCallable)
	void UpdateTowerState(ETowerState State);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnemyEnteredTheRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEnemyExitedTheRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AProjectile* SpawnProjectile();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool FindTarget();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Seek();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopFire();
	
	virtual void Interact_Implementation() override;

	virtual void Disassociate_Implementation() override;

	//Projectile Pooling Methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallPooledProjectile();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnProjectilePool();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnProjectileJobComplete(class AProjectile* Projectile);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnProjectileDealtDamage();

	// Upgrades
	virtual void Upgrade_Implementation(FUpgradeDetails Details) override;

	virtual void DestructBuilding_Implementation() override;
};
