// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	
}

void AProjectile::DeactivateProjectile_Implementation()
{
}

void AProjectile::ActivateProjectile_Implementation(AActor* Target)
{
	mTarget = Target;
}
