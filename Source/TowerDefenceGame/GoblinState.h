// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GoblinState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AGoblinState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	int mStartingResources;

	virtual void BeginPlay() override;
};
