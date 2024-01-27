// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceClasses/PlayerInputInterface.h"
#include "UIClasses/PlayerHUD.h"
#include "SpecPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ASpecPlayer : public APawn, public IPlayerInputInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UPlayerHUD* pHud;

	virtual void Move_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void Look_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void EnableLook_Implementation() override;
	virtual void DisableLook_Implementation() override;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FVector CalculateSnappedPosition(FVector HitLocation, float SnapInterval);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingSpawn(class ABaseBuilding* NewBuilding);
	

};
