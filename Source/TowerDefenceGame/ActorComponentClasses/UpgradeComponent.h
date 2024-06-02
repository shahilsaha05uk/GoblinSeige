// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerDefenceGame/ObjectClasses/UpgradeObject.h"
#include "TowerDefenceGame/SupportClasses/StructClass.h"
#include "UpgradeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeAppliedSignature, FUpgradeDetails, Details);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENCEGAME_API UUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	FUpgradeDetails mCurrentUpgrade;
	UPROPERTY()
	int mTotalMoneySpentOnUpgrades;

	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnUpgradeAppliedSignature OnUpgradeApplied;
	UPROPERTY(BlueprintReadOnly)
	TArray<FUpgradeDetails> mUpgradeDetails;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUpgradeObject> UpgradeClass;
	UPROPERTY(BlueprintReadOnly)
	class UResourceSubsystem* mResourceSubsystem;

	UUpgradeComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	void Init(UDA_UpgradeAsset* UpgradeAsset);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTotalMoneySpentOnUpgrades() { return mTotalMoneySpentOnUpgrades; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsValidUpgrade() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FUpgradeDetails GetCurrentUpgrade() {return mCurrentUpgrade;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasNextUpgrade() const;
	UFUNCTION(BlueprintCallable)
	void MoveToNextUpgrade();
	UFUNCTION(BlueprintCallable)
	void ApplyUpgrade();
};
