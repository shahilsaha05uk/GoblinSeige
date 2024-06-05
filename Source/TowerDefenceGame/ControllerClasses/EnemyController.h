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
	class UGameSubsystem* mGameSubsytem;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int, TSubclassOf<class ABaseEnemy>> mEnemyClassMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ABaseEnemy* EnemyRef;

	virtual void BeginPlay() override;

	virtual void OnUnPossess() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnPawn(FVector SpawnPoint, int Type);

	virtual void EnemyMove_Implementation(class ASpline* Spline) override;
	virtual void EnemyAttack_Implementation() override;
	

	// Phase Methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPhaseComplete(int Phase);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGameComplete(bool bWon);

};
