// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "NiagaraComponent.h"
#include "Projectile.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefenceGame/UIClasses/TowerUI.h"

// Sets default values
ATower::ATower()
{
	mRangeColliderComp = CreateDefaultSubobject<USphereComponent>("RangeComp");
	RootComponent = mRangeColliderComp;
	
	mStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("TowerBase");
	mStaticMeshComp->SetupAttachment(RootComponent);

	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>("TowerNiagara");
	mNiagaraComp->SetupAttachment(mStaticMeshComp);

	mTowerWidgetComp = CreateDefaultSubobject<UWidgetComponent>("TowerWidgetComp");
	mTowerWidgetComp->SetupAttachment(RootComponent);

	mStaticMeshSelectedComp->SetupAttachment(RootComponent);
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	mRangeColliderComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnemyEnteredTheRange);
	mRangeColliderComp->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEnemyExitedTheRange);

}

void ATower::Init_Implementation(FBuildingBuyDetails BuildingDetails)
{
	Super::Init_Implementation(BuildingDetails);
	mTowerUI = Cast<UTowerUI>(mTowerWidgetComp->GetWidget());

	if(mTowerUI)
		mTowerUI->ToggleWidgetSwitcher(ConfirmWidget);
	
	mNiagaraComp->SetAsset(BuildingDetails.mBuildingNiagara, true);
}

void ATower::OnBuildingDecisionTaken_Implementation(EBuildStatus Status)
{
	Super::OnBuildingDecisionTaken_Implementation(Status);
	mTowerUI->ToggleWidgetSwitcher(NoWidget);
}

void ATower::OnEnemyEnteredTheRange_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ATower::OnEnemyExitedTheRange_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
}

void ATower::Fire_Implementation()
{
	if(bShouldPool)
	{
		OnProjectilePool();
		return;
	}
}

void ATower::StopFire_Implementation()
{
	for (auto p : mPooledProjectiles)
	{
		p->Destroy();
	}
}

void ATower::OnProjectilePool_Implementation()
{
	if(PoolCount <= ProjectilePoolCount)
	{
		if(const auto projectile = SpawnProjectile())
		{
			projectile->OnProjectileJobComplete.AddDynamic(this, &ThisClass::OnProjectileJobComplete);
			projectile->ActivateProjectile();
			mPooledProjectiles.Add(projectile);
			PoolCount++;
		}
	}
	else CallPooledProjectile();
}

void ATower::CallPooledProjectile_Implementation()
{
	if(tempPoolCount < PoolCount-1) tempPoolCount++;
	else tempPoolCount = 0;
	if(const auto proj = mPooledProjectiles[tempPoolCount])
		proj->ActivateProjectile();

}

AProjectile* ATower::SpawnProjectile_Implementation()
{
	return nullptr;
}

void ATower::OnProjectileJobComplete_Implementation(AProjectile* Projectile)
{
	
}

void ATower::Interact_Implementation()
{
	Super::Interact_Implementation();
	mTowerUI->ToggleWidgetSwitcher(UpgradeWidget);
	mTowerUI->SetVisibility(ESlateVisibility::Visible);
}

void ATower::Disassociate_Implementation()
{
	Super::Disassociate_Implementation();
	mTowerUI->ToggleWidgetSwitcher(NoWidget);
	mTowerUI->SetVisibility(ESlateVisibility::Hidden);
}