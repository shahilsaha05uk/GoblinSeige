// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "TowerDefenceGame/ControllerClasses/EnemyController.h"
#include "TowerDefenceGame/SubsystemClasses/EnemySubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/WaveSubsystem.h"

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	mEnemySubsystem = GetGameInstance()->GetSubsystem<UEnemySubsystem>();
	if(mEnemySubsystem)
	{
		mEnemySubsystem->OnEnemyDead.AddDynamic(this, &ThisClass::FreeController);
	}

	mWaveSubsystem = GetGameInstance()->GetSubsystem<UWaveSubsystem>();
	if(mWaveSubsystem)
	{
		mWaveSubsystem->OnWaveStarted.AddDynamic(this, &ThisClass::PrepareForWave);
	}
}

void AEnemyManager::CacheControllers_Implementation(int ControllerCount)
{
	for (int i = 0; i < ControllerCount; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Controller %d"), i);
		AEnemyController* EController = GetWorld()->SpawnActor<AEnemyController>(mEnemyControllerClass);

		mFreeControllers.Add(EController);
		TotalEnemyControllers++;
	}
}

void AEnemyManager::AssignEnemy_Implementation(int EnemyID)
{
	if(mFreeControllers.IsEmpty()) return;
	const auto SpawnPoint = mEnemySubsystem->GetRandomEnemySpawnPoint();

	const auto Controller = mFreeControllers.Pop(true);	// take out a free controller
	Controller->SpawnPawn(SpawnPoint, EnemyID);	// spawn the pawn

	TotalEnemyControllersAssigned++;
}

void AEnemyManager::GameOver_Implementation()
{
	FlushEverything();
}

#pragma region Spawners
void AEnemyManager::PrepareForWave_Implementation(int Wave)
{
	if(WaveRangeConfigurations.Contains(Wave))
	{
		mLatestWaveConfigs = WaveRangeConfigurations[Wave];
	}
	mRemainingEnemies = mLatestWaveConfigs.TotalEnemies;

	int RequiredControllers = 0;
		
	if(!HasEnoughControllers(RequiredControllers))
		CacheControllers(RequiredControllers);
	
	SpawnFixedEnemies(mLatestWaveConfigs.FixedEnemies);
	SpawnProbableEnemies(mLatestWaveConfigs.EnemyProbabilities);

}

void AEnemyManager::SpawnFixedEnemies_Implementation(const TArray<FFixedEnemy>& FixedEnemyData)
{
	for (const auto &data : FixedEnemyData)
	{
		const int Count = data.Count;
		const int ID = data.EnemyLevel;
		for (int i = 0; i < Count; i++)
		{
			AssignEnemy(ID);
			mRemainingEnemies--;
		}
	}
}

void AEnemyManager::SpawnProbableEnemies_Implementation(const TArray<FEnemyProbability>& ProbableData)
{
	// Normalize the probabilities to ensure they sum to 1
	TArray<FEnemyProbability> NormalizedProbabilities = mLatestWaveConfigs.EnemyProbabilities;
	NormalizeProbabilities(NormalizedProbabilities);
	
	// Calculate cumulative probabilities for random enemy selection
	TArray<float> CumulativeProbabilities;
	float CumulativeSum = 0.0f;

	for (const FEnemyProbability& EnemyProb : NormalizedProbabilities)
	{
		CumulativeSum += EnemyProb.Probability;
		CumulativeProbabilities.Add(CumulativeSum);
	}

	// Spawn Remaining Enemies Based on Probabilities
	while (mRemainingEnemies > 0)
	{
		float RandomValue = FMath::FRand();

		for (int32 i = 0; i < NormalizedProbabilities.Num(); ++i)
		{
			if (RandomValue <= CumulativeProbabilities[i])
			{
				AssignEnemy(NormalizedProbabilities[i].EnemyLevel);
				break;
			}
		}
		--mRemainingEnemies;
	}
}

#pragma endregion

#pragma region Checkers

bool AEnemyManager::HasEnoughControllers(int &RequiredControllers)
{
	RequiredControllers = mRemainingEnemies - mFreeControllers.Num();
	return RequiredControllers <= 0;
}

#pragma endregion

#pragma region Maths
void AEnemyManager::NormalizeProbabilities(TArray<FEnemyProbability>& Probabilities)
{
	float TotalProbability = 0.0f;
	for (const FEnemyProbability& EnemyProb : Probabilities)
	{
		TotalProbability += EnemyProb.Probability;
	}

	if (TotalProbability > 0.0f)
	{
		for (FEnemyProbability& EnemyProb : Probabilities)
		{
			EnemyProb.Probability /= TotalProbability;
		}
	}
}

#pragma endregion

#pragma region Cleaners
void AEnemyManager::FreeController(AEnemyController* ControllerRef)
{
	if(!mFreeControllers.Contains(ControllerRef))
	{
		mFreeControllers.Add(ControllerRef);
		TotalEnemyControllersAssigned--;
	}
	if(TotalEnemyControllersAssigned == 0)
	{
		if(mWaveSubsystem) mWaveSubsystem->EndWave();
	}
}

void AEnemyManager::FlushEverything()
{
	for (auto c : mFreeControllers)
		c->Destroy();

	mFreeControllers.Empty();
}

#pragma endregion
