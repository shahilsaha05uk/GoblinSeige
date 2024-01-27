// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveUpdateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveStartSignature);

UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


	// Game Progression
private:

	int mInitialWave;
	int mCurrentWave;
	int mFinalWave;
	

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWaveStartSignature OnWaveStartSignature;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWaveUpdateSignature OnWaveUpdateSignature;

	UFUNCTION(BlueprintCallable)
	int GetWave(ELevel level);
	
	UFUNCTION(BlueprintCallable)
	void UpdateWave();
	
	
	
};
