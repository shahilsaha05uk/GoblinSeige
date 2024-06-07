// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	
}

void AProjectile::Init(FOnProjectileUpgradeSignature OnUpgradeSignature)
{
	OnUpgradeSignature.AddDynamic(this, &ThisClass::OnUpgrade);
}

void AProjectile::OnUpgrade_Implementation(FProjectileDetails ProjectileDetails)
{
}

void AProjectile::ActivateProjectile_Implementation(AActor* Target, float MinSpeed, float MaxSpeed)
{
	
}

void AProjectile::DeactivateProjectile_Implementation()
{
}