 // Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenceGameGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);

UCLASS()
class TOWERDEFENCEGAME_API ATowerDefenceGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	class APlayerController* mPlayerController;

	UPROPERTY(EditDefaultsOnly)
	int mStartingResources;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWaveManager> WaveManagerClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyManager> EnemyManagerClass;
public:

	UPROPERTY(BlueprintReadOnly)
	class AWaveManager* mWaveManager;
	UPROPERTY(BlueprintReadOnly)
	class AEnemyManager* mEnemyManager;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameOverSignature OnGameOver;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDoorBroken();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameOver();
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
