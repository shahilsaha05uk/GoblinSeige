// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/BaseClasses/BaseEnemy.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/DataAssetClasses/DA_UpgradeAsset.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"

// Sets default values
ATurret::ATurret()
{
	//OnTurretActivateSignature.AddDynamic(this, &ATurret::PowerOn);
	RangeCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnRangeBeginOverlap);
	RangeCollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnRangeEndOverlap);
}


void ATurret::OnInteract_Implementation()
{
	RangeDecalComp->SetVisibility(true);
	Super::OnInteract_Implementation();
}

void ATurret::OnDisassociate_Implementation()
{
	RangeDecalComp->SetVisibility(false);
	Super::OnDisassociate_Implementation();
}

void ATurret::PostBuild_Implementation()
{
	Super::PostBuild_Implementation();

	RangeDecalComp->SetVisibility(false);
	//PowerOn();
}


void ATurret::LookAtTarget_Implementation()
{
	
}

void ATurret::IncreaseRange_Implementation()
{
	const float attackRange = BuildingDetails.BuildingStats.AttackRange;
	const float decalSize = attackRange / 100.f;

	RangeCollisionComp->SetSphereRadius(attackRange, true);
	RangeDecalComp->SetRelativeScale3D(FVector(1.0f, decalSize, decalSize));
}


void ATurret::OnRangeBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Other Actor Begin: %s"), *OtherActor->GetName());
		Targets.AddUnique(OtherActor);
		FindTarget();
	}
}

void ATurret::OnRangeEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		
		if(!Targets.IsEmpty() && Targets.Contains(OtherActor))
		{
			Targets.Remove(OtherActor);

			FindTarget();

		}
		else
		{
			CurrentTarget = nullptr;
		}
	}
}

AActor* ATurret::FindTarget_Implementation()
{
	CurrentTarget = nullptr;
	Targets.Shrink();
	float attackRange = BuildingDetails.BuildingStats.AttackRange;
	AActor* foundTarget = UGameplayStatics::FindNearestActor(GetActorLocation(), Targets, attackRange);
	if(foundTarget) OnFoundTarget(foundTarget);
	return foundTarget;
}

void ATurret::OnFoundTarget_Implementation(AActor* FoundTarget)
{
	if(Targets.IsEmpty()) PowerOff();
	else PowerOn();
}

void ATurret::PowerOn_Implementation()
{
	if(bIsPowerOn) return;
	
	if(ShouldTurnOnFiring)
	{
		GetWorldTimerManager().SetTimer(FireTimerHandler, this, &ThisClass::Fire,  BuildingDetails.BuildingStats.AttackSpeed, FireShouldLoop, 0.0f);
	}

	if(bHasRotator)
		GetWorldTimerManager().SetTimer(TurningTimeHandler, this, &ThisClass::LookAtTarget, RotationTimeInterval, RotatorShouldLoop, 0.0f);

	bIsPowerOn = true;
}

void ATurret::PowerOff_Implementation()
{
	if(!bIsPowerOn) return;

	bAttacking = false;

	GetWorldTimerManager().ClearTimer(FireTimerHandler);
	GetWorldTimerManager().ClearTimer(TurningTimeHandler);

	bIsPowerOn = false;
}


void ATurret::Fire_Implementation()
{
	Execute_PlaySound(this);
}

void ATurret::StopFire_Implementation()
{
	PowerOff();
}

void ATurret::SpawnProjectile_Implementation(TSubclassOf<AProjectile> ProjectileClass, FVector Location, FRotator Rotation, AActor* Target)
{
}

void ATurret::Upgrade_Implementation()
{
	Super::Upgrade_Implementation();

	if(bIsPowerOn) PowerOff();
	PowerOn();
}