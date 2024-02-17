// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
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

void ATurret::Init_Implementation(UDA_BuildingAsset* asset)
{
	Super::Init_Implementation(asset);
}

void ATurret::OnSelect_Implementation()
{
	RangeDecalComp->SetVisibility(true);
}

void ATurret::OnDeselect_Implementation()
{
	RangeDecalComp->SetVisibility(false);
}

void ATurret::PostBuild_Implementation()
{
	Super::PostBuild_Implementation();

	UpdateBuildingStats(BuildingAsset->BuildingStats);

	RangeDecalComp->SetVisibility(false);

	PowerOn();

}

void ATurret::Upgrade_Implementation()
{
	if(!isUpgradeAvailable()) return;

	UpdateBuildingStats(UpgradeAsset->BuildingStats);
	
	Super::Upgrade_Implementation();
}

void ATurret::UpdateBuildingStats_Implementation(FBuildingStats stats)
{
	AttackRange = stats.AttackRange;
	AttackDamage = stats.AttackDamage;
	AttackSpeed = stats.AttackSpeed;
	

	IncreaseRange();
}

void ATurret::OnBuildingBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBuildingBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ATurret::OnBuildingEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnBuildingEndOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void ATurret::LookAtTarget_Implementation()
{
	
}

void ATurret::IncreaseRange_Implementation()
{
	RangeCollisionComp->SetSphereRadius(AttackRange, true);
	const float decalSize = AttackRange / 100.f;
	RangeDecalComp->SetRelativeScale3D(FVector(1.0f, decalSize, decalSize));
}

void ATurret::OnRangeBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Other Actor Begin: %s"), *OtherActor->GetName());
		Targets.AddUnique(OtherActor);
		ClosestTarget = FindTarget();
		SetTarget();
		
	}
}

void ATurret::OnRangeEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Other Actor End: %s"), *OtherActor->GetName());
		if(!Targets.IsEmpty() && Targets.Contains(OtherActor))
		{
			Targets.Remove(OtherActor);

			ClosestTarget = FindTarget();

			SetTarget();
		}
		else
		{
			CurrentTarget = nullptr;
			ClosestTarget = nullptr;

			//OnNoTargetInRange();
		}
	}
}

AActor* ATurret::FindTarget_Implementation()
{
	AActor* foundTarget = UGameplayStatics::FindNearestActor(GetActorLocation(), Targets, AttackRange);
	if(foundTarget) OnFoundTarget(foundTarget);
	return foundTarget;
}

void ATurret::OnFoundTarget_Implementation(AActor* FoundTarget)
{
	if(Targets.IsEmpty()) PowerOff();
	else PowerOn();

	if(CurrentTarget == nullptr || CurrentTarget != FoundTarget)
		CurrentTarget = FoundTarget;
}


void ATurret::PowerOn_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Power On"));
	if(bIsPowerOn) return;
	
	if(ShouldTurnOnFiring)
		GetWorldTimerManager().SetTimer(FireTimerHandler, this, &ThisClass::Fire, AttackSpeed, FireShouldLoop, 0.0f);

	if(bHasRotator)
		GetWorldTimerManager().SetTimer(TurningTimeHandler, this, &ThisClass::LookAtTarget, RotationTimeInterval, RotatorShouldLoop, 0.0f);
}

void ATurret::PowerOff_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Power Off"));
	if(!bIsPowerOn) return;

	bAttacking = false;

	GetWorldTimerManager().ClearTimer(FireTimerHandler);
	GetWorldTimerManager().ClearTimer(TurningTimeHandler);

}

void ATurret::StartFire_Implementation()
{
	
}

void ATurret::Fire_Implementation()
{
	
}

void ATurret::StopFire_Implementation()
{
	
}

void ATurret::SpawnProjectile_Implementation(TSubclassOf<AProjectile> ProjectileClass, FVector Location, FRotator Rotation, AActor* Target)
{
}

void ATurret::SetTarget_Implementation()
{
	if(Targets.Contains(CurrentTarget)) return;

	CurrentTarget = ClosestTarget;
}

