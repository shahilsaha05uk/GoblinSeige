// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "Kismet/KismetMathLibrary.h"
#include "TowerDefenceGame/ControllerClasses/EnemyController.h"
#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	mEnemySubsystem = GetGameInstance()->GetSubsystem<UEnemySubsystem>();
	if(mEnemySubsystem)
	{
		mEnemySubsystem->OnEnemyDead.AddDynamic(this, &ThisClass::FreeController);
	}
	if(const auto WaveSubs = GetGameInstance()->GetSubsystem<UWaveSubsystem>())
	{
		WaveSubs->OnWaveStarted.AddDynamic(this, &ThisClass::PrepareForWave);
	}
}

void AEnemyManager::CacheControllers()
{
	const int CacheControllerCount = TotalEnemiesToSpawnThisRound;
	for (int i = 0; i < CacheControllerCount; i++)
	{
		auto EController= GetWorld()->SpawnActor<AEnemyController>(mEnemyControllerClass);
		mFreeControllers.Add(EController);
	}
}

void AEnemyManager::SpawnEnemies()
{
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimerHandle, this, &ThisClass::RequestEnemy, 1.0f, true);
}

void AEnemyManager::InitSub(TSubclassOf<AEnemyController> EnemyControllerClass)
{
	mEnemyControllerClass = EnemyControllerClass;
}

void AEnemyManager::RequestEnemy()
{
	if(TotalEnemiesToSpawnThisRound-- == 0 || mFreeControllers.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandle);
		EnemySpawnTimerHandle.Invalidate();
		return;
	}

	// Clear and invalidate the timer if the remaining enemies to spawn is 0
	const auto SpawnPoint = mEnemySubsystem->GetRandomEnemySpawnPoint();

	const auto Controller = mFreeControllers.Pop(true);	// take out a free controller
	Controller->SpawnPawn(SpawnPoint);	// spawn the pawn
	mAllocatedController.Add(Controller);	// add it to the allocated controller
}

void AEnemyManager::FreeController(AEnemyController* EnemyController)
{
	if(mAllocatedController.Contains(EnemyController))
	{
		mAllocatedController.Remove(EnemyController);
		mFreeControllers.Add(EnemyController);
	}
}

void AEnemyManager::PrepareForWave(int Wave)
{
	TotalEnemiesToSpawnThisRound = GetRandomEnemyCounts(Wave);

	// check if there are enough free controllers
	if(mFreeControllers.IsEmpty() || mFreeControllers.Num() < TotalEnemiesToSpawnThisRound)
	{
		CacheControllers();
	}
	if(mFreeControllers.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Controllers Available"));
		return;
	}
	
	SpawnEnemies();
}

void AEnemyManager::FlushEverything()
{
}

int AEnemyManager::GetRandomEnemyCounts(int Wave)
{
	return UKismetMathLibrary::RandomIntegerInRange(Wave, (Wave + 2));
}

void AEnemyManager::GameOver_Implementation()
{
	FlushEverything();
}
