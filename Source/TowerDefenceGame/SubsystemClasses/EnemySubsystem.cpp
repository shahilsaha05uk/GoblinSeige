// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySubsystem.h"

#include "Kismet/KismetMathLibrary.h"
#include "TowerDefenceGame/ControllerClasses/EnemyController.h"

void UEnemySubsystem::InitSub(TSubclassOf<AEnemyController> EnemyControllerClass)
{
	mEnemyControllerClass = EnemyControllerClass;
}

void UEnemySubsystem::PrepareForWave(int Wave)
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
void UEnemySubsystem::FlushEverything()
{
	for (auto c : mFreeControllers)
		c->Destroy();

	for (auto c : mAllocatedController)
		c->Destroy();
	
	mFreeControllers.Empty();
	mAllocatedController.Empty();
}

#pragma region Privates

void UEnemySubsystem::CacheControllers()
{
	const int CacheControllerCount = TotalEnemiesToSpawnThisRound;
	for (int i = 0; i < CacheControllerCount; i++)
	{
		auto EController= GetWorld()->SpawnActor<AEnemyController>(mEnemyControllerClass);
		mFreeControllers.Add(EController);
	}
}

void UEnemySubsystem::SpawnEnemies()
{
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimerHandle, this, &ThisClass::RequestEnemy, 1.0f, true);
}

void UEnemySubsystem::RequestEnemy()
{
	if(TotalEnemiesToSpawnThisRound-- == 0 || mFreeControllers.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandle);
		EnemySpawnTimerHandle.Invalidate();
		return;
	}

	// Clear and invalidate the timer if the remaining enemies to spawn is 0
	const auto SpawnPoint = GetRandomEnemySpawnPoint();

	const auto Controller = mFreeControllers.Pop(true);	// take out a free controller
	Controller->SpawnPawn(SpawnPoint);	// spawn the pawn
	mAllocatedController.Add(Controller);	// add it to the allocated controller
}

void UEnemySubsystem::FreeController(AEnemyController* EnemyController)
{
	if(mAllocatedController.Contains(EnemyController))
	{
		mAllocatedController.Remove(EnemyController);
		mFreeControllers.Add(EnemyController);
	}
}

#pragma endregion

#pragma region Register Spawn Points

void UEnemySubsystem::RegisterSpawnPoint(AEnemySpawnPoint* SpawnPoint)
{
	if(!mSpawnPoints.Contains(SpawnPoint))
	{
		mSpawnPoints.Add(SpawnPoint);
		EnemySpawnPointCount++;
	}
}

void UEnemySubsystem::DeRegisterSpawnPoint()
{
	mSpawnPoints.Empty();
}


#pragma endregion

#pragma region Getters
int UEnemySubsystem::GetRandomEnemyCounts(int Wave)
{
	return UKismetMathLibrary::RandomIntegerInRange(Wave, (Wave + 2));
}

AEnemySpawnPoint* UEnemySubsystem::GetRandomEnemySpawnPoint()
{
	int rand = FMath::RandRange(0, EnemySpawnPointCount);
	return mSpawnPoints[rand];
}

#pragma endregion