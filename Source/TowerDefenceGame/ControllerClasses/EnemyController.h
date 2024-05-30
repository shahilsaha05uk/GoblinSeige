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
	UPROPERTY(EditDefaultsOnly)
	TMap<int, TSubclassOf<class ABaseEnemy>> mEnemyClassMap;

	class AEnemyManager* mEnemyManager;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UBehaviorTree* BehaviorTreeRef;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ABaseEnemy* EnemyRef;
	
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnPawn(AEnemySpawnPoint* SpawnBox);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnControllerDestroy();

	virtual void EnemyMove_Implementation(FVector TargetLocation) override;
	virtual void EnemyAttack_Implementation() override;
	
	virtual bool EnemyHasAValidPath_Implementation() override;

};
