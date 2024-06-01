// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementActor.h"
#include "TowerDefenceGame/DataAssetClasses/DA_BuildingAsset.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInputInterface.h"
#include "TowerDefenceGame/InterfaceClasses/PlayerInterface.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "SpecPlayer.generated.h"




UCLASS()
class TOWERDEFENCEGAME_API ASpecPlayer : public APawn, public IPlayerInputInterface, public IPlayerInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float CurrentAngle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Orbit")
	float MinPitchAngle;
	UPROPERTY(EditDefaultsOnly, Category = "Orbit")
	float MaxPitchAngle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Orbit")
	TSubclassOf<AActor> mOrbitActorClass;
	UPROPERTY()
	AActor* mOrbitActor;
	UPROPERTY()
	FVector mOrbitCenter;
	
	UPROPERTY()
	float mCurrentYawAngle;
	float mCurrentPitchAngle;

	UFUNCTION()
	void CalculateInitialAngles();
	UFUNCTION()
	void UpdateCameraPosition();
public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit")
	float OrbitRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit")
	float OrbitSpeed;
	

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UTimerComponent* mTimerComp;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UCameraComponent* mCameraComp;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USpringArmComponent* mSpringArmComp;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UBuildingPlacementHandlerComponent* mBuildingPlacementHandlerComponent;

	ASpecPlayer();

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	void OnHudInitialised(AHUD* HudRef);
	
	UPROPERTY(BlueprintReadOnly)
	class UPlayerHUD* mPlayerHUD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class AInputController* ControllerRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	int mStartingResources;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	FTimerHandle OnSpawnTimeHandler;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Building Properties")
	TEnumAsByte<ETraceTypeQuery> BuildingTraceChannel;
	
	virtual void Move_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void Look_Implementation(const FInputActionValue& InputActionValue) override;
	virtual void EnableLook_Implementation() override;
	virtual void DisableLook_Implementation() override;
	virtual void LeftMouseActions_Implementation() override;
	virtual void Zoom_Implementation(float Value) override;
};
