// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameGameModeBase.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	class APlayerController* mPlayerController;

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;


	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AWaveManager* GetWaveManager(){return mWaveManager; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AEnemyManager* GetEnemyManager() { return mEnemyManager; }
	
protected:

	UPROPERTY(BlueprintReadWrite, Category = "Managers")
	class AWaveManager* mWaveManager;
	
	UPROPERTY(BlueprintReadWrite, Category = "Managers")
	class AEnemyManager* mEnemyManager;
};
