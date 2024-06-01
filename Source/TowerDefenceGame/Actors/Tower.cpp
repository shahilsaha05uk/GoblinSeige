// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "NiagaraComponent.h"
#include "Projectile.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/BaseClasses/BaseEnemy.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"
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

	UpdateTowerState(ETowerState::Idle);
}

void ATower::Init_Implementation(FBuildingBuyDetails BuildingDetails)
{
	Super::Init_Implementation(BuildingDetails);
	mTowerUI = Cast<UTowerUI>(mTowerWidgetComp->GetWidget());

	if(mTowerUI)
		mTowerUI->ToggleWidgetSwitcher(ConfirmWidget);
	
	mNiagaraComp->SetAsset(BuildingDetails.mBuildingNiagara, true);
}

#pragma region States

void ATower::Fire_Implementation()
{
	if(!mTarget)
	{
		if(!FindTarget())
		{
			UpdateTowerState(ETowerState::Idle);
		}
	}
	else
	{
		if(bShouldPool)
		{
			OnProjectilePool();
		}
	}
}

void ATower::StopFire_Implementation()
{
	// if there are no more targets in the range, destroy the projectiles
	for (auto p : mPooledProjectiles)
	{
		p->Destroy();
	}
	UpdateTowerState(ETowerState::Seek);
}

void ATower::Seek_Implementation()
{
	if(FindTarget())
		UpdateTowerState(ETowerState::Firing);
}

#pragma endregion

#pragma region Interact

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

#pragma endregion

#pragma region Pooling Projectile

void ATower::OnProjectileJobComplete_Implementation(AProjectile* Projectile)
{
	
}

void ATower::OnProjectilePool_Implementation()
{
	if(PoolCount <= ProjectilePoolCount)
	{
		if(const auto projectile = SpawnProjectile())
		{
			projectile->OnProjectileJobComplete.AddDynamic(this, &ThisClass::OnProjectileJobComplete);
			if(mTarget) projectile->ActivateProjectile(mTarget);
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
	{
		if(mTarget) proj->ActivateProjectile(mTarget);
	}
}

#pragma endregion

#pragma region Overlapped

void ATower::OnEnemyEnteredTheRange_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UEnemyInterface::StaticClass()) && TowerState != Firing)
	{
		UpdateTowerState(Firing);
	}
}

void ATower::OnEnemyExitedTheRange_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	// if the actor that ended overlapped is the same as the target, then find a new target
	if(mTarget == OtherActor)
	{
		UpdateTowerState(ETowerState::Seek);
	}
}

#pragma endregion

#pragma region Privates

void ATower::OnBuildingDecisionTaken_Implementation(EBuildStatus Status)
{
	Super::OnBuildingDecisionTaken_Implementation(Status);
	mTowerUI->ToggleWidgetSwitcher(NoWidget);
}

void ATower::UpdateTowerState(ETowerState State)
{
	GetWorld()->GetTimerManager().ClearTimer(TowerStateTimeHandler);
	TowerStateTimeHandler.Invalidate();

	TowerState = State;

	switch (TowerState) {
	case ETowerState::Firing:
		GetWorld()->GetTimerManager().SetTimer(TowerStateTimeHandler, this, &ThisClass::Seek, BuildingStats.RateOfFire, true);
		Fire();
		break;
	case ETowerState::Seek:
		GetWorld()->GetTimerManager().SetTimer(TowerStateTimeHandler, this, &ThisClass::Seek, mSeekRate, true);
		break;
	case ETowerState::Idle:
		StopFire();
		break;
	}
}

AProjectile* ATower::SpawnProjectile_Implementation()
{
	return nullptr;
}

bool ATower::FindTarget_Implementation()
{
	TArray<AActor*> OverlappedActors;
	mRangeColliderComp->GetOverlappingActors(OverlappedActors, ABaseEnemy::StaticClass());

	if(!OverlappedActors.IsEmpty())
	{
		float Distance = 0.0f;
		mTarget = UGameplayStatics::FindNearestActor(GetActorLocation(), OverlappedActors, Distance);
	}
	return (mTarget != nullptr);
}

#pragma endregion
