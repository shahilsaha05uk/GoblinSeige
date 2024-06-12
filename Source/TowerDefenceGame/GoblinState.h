// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SupportClasses/StructClass.h"
#include "GoblinState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API AGoblinState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	class UResourceSubsystem* mResourceSubsystem;
	
	UPROPERTY(EditDefaultsOnly)
	int mStartingResources;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPhaseLoaded(int LoadedPhase, FPhaseDetails PhaseDetails);

};
