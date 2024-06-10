// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "PhaseManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoTargetsLeftSignature);

UCLASS()
class TOWERDEFENCEGAME_API APhaseManager : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	int mTotalTargetsToDestroy = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	int mCurrentPhase = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	int mFinalPhase = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Phase")
	TArray<ULevel*> LevelsToSelect;
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnNoTargetsLeftSignature OnNoTargetsLeft;
	
	UPROPERTY(BlueprintReadOnly)
	class ATowerDefenceGameGameModeBase* mGameMode;
	UPROPERTY(BlueprintReadOnly)
	class UGameSubsystem* mGameSubsystem;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Phase", meta = (ToolTip = "Key: Phase; Value: Phase Details"))
	TMap<int, FPhaseDetails> mPhaseDetails;
	
	UPROPERTY(BlueprintReadOnly, Category = "Phase")
	FPhaseDetails mCurrentPhaseDetails;

	virtual void BeginPlay() override;

	//Privates
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(class ATowerDefenceGameGameModeBase* GameMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool LoadPhase();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TargetDestroyed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdatePhase();
	
	// on loading/unloading finish
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPhaseLoaded();

	// Updaters
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTargets();

	//Getters
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetTotalTargetsToDestroy() {return mTotalTargetsToDestroy;}
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentPhase() { return mCurrentPhase; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetTotalPhases() {return mFinalPhase; }

	// Checkers
	UFUNCTION(BlueprintPure)
	bool HasDestroyedAllTheTargets() const {return (mTotalTargetsToDestroy == 0);}
	UFUNCTION(BlueprintPure)
	bool HasPhasesLeft() const { return mCurrentPhase <= mFinalPhase; }
};
