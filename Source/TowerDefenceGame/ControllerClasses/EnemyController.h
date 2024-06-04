// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyControllerInterface.h"
#include "EnemyController.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AEnemyController : public AAIController, public IEnemyControllerInterface
{
	GENERATED_BODY()

private:
	class AEnemyManager* mEnemyManager;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int, TSubclassOf<class ABaseEnemy>> mEnemyClassMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ABaseEnemy* EnemyRef;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitController(AEnemyManager* EnemyManager);

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnPawn(class AEnemySpawnPoint* SpawnBox, int Type);

	virtual void EnemyMove_Implementation(class ASpline* Spline) override;
	virtual void EnemyAttack_Implementation() override;
	

	// Phase Methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPhaseComplete(int Phase);

};
