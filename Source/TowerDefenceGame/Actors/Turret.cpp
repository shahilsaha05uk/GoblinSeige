// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"

// Sets default values
ATurret::ATurret()
{
	OnTurretActivateSignature.AddDynamic(this, &ATurret::PowerOn);
	RangeCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnRangeBeginOverlap);
	RangeCollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnRangeEndOverlap);
}

void ATurret::PowerOn_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Power On"));
}

void ATurret::IncreaseRange_Implementation()
{
	RangeCollisionComp->SetSphereRadius(AttackRange, true);
	const float decalSize = AttackRange / 100.f;
	RangeDecalComp->SetRelativeScale3D(FVector(1.0f, decalSize, decalSize));
}

void ATurret::OnRangeBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Actor Begin: %s"), *OtherActor->GetName());
		Targets.AddUnique(OtherActor);
		ClosestTarget = FindTarget();
		SetTarget();

		//FindTarget();
	}
}

void ATurret::OnRangeEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Other Actor End: %s"), *OtherActor->GetName());
		if(!Targets.IsEmpty() && Targets.Contains(OtherActor))
		{
			Targets.Remove(OtherActor);

			float distance;
			ClosestTarget = UGameplayStatics::FindNearestActor(GetActorLocation(), Targets, distance);

			SetTarget();
			FindTarget();
		}
		else
		{
			CurrentTarget = nullptr;
			ClosestTarget = nullptr;

			OnNoTargetInRange();
		}
	}
}


AActor* ATurret::FindTarget_Implementation()
{
	return UGameplayStatics::FindNearestActor(GetActorLocation(), Targets, AttackRange);
}

void ATurret::OnNoTargetInRange_Implementation()
{
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

