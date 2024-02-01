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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	FTimerHandle OnSpawnTimeHandler;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	ABaseBuilding* tempBuilding;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	ABaseBuilding* selectBuilding;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	TEnumAsByte<ETraceTypeQuery> BuildingMovementTraceChannel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	TEnumAsByte<ETraceTypeQuery> BuildingTraceChannel;

	virtual void Move_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void Look_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void EnableLook_Implementation() override;
	virtual void DisableLook_Implementation() override;
	virtual void LeftMouseActions_Implementation() override;
	virtual void Zoom_Implementation(float Value) override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuildingSpawn(class ABaseBuilding* NewBuilding);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Build();
};
