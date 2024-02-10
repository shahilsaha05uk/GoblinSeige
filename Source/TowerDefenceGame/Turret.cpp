// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "InterfaceClasses/EnemyInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATurret::ATurret()
{
	RangeCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnRangeBeginOverlap);
	RangeCollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnRangeEndOverlap);
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
		Targets.AddUnique(OtherActor);
		float distance;
		ClosestTarget = UGameplayStatics::FindNearestActor(GetActorLocation(), Targets, distance);
		IdentifyTarget();
	}
}

void ATurret::OnRangeEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()))
	{
		if(!Targets.IsEmpty() && Targets.Contains(OtherActor))
		{
			Targets.Remove(OtherActor);

			float distance;
			ClosestTarget = UGameplayStatics::FindNearestActor(GetActorLocation(), Targets, distance);
			IdentifyTarget();

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


void ATurret::FindTarget_Implementation()
{
}

void ATurret::OnNoTargetInRange_Implementation()
{
}

void ATurret::Fire_Implementation()
{
}

void ATurret::IdentifyTarget_Implementation()
{
	if((ClosestTarget == nullptr) || (Targets.Contains(ClosestTarget))) return;

	CurrentTarget = ClosestTarget;
}

