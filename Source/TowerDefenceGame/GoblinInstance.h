// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InterfaceClasses/GameInstanceInterface.h"
#include "GoblinInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UGoblinInstance : public UGameInstance, public IGameInstanceInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int mInitialWave = 1;
	UPROPERTY(EditDefaultsOnly)
	int mFinalWave;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyController> mEnemyControllerClass;
	
public:

	virtual void Init() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level Map")
	TMap<TEnumAsByte<ELevelToTravel>, TSoftObjectPtr<UWorld>> LevelMap;

	virtual void TravelToMap_Implementation(ELevelToTravel LevelToTravel) override;

};
