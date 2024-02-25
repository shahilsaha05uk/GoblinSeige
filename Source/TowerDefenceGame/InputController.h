#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "TowerDefenceGameGameModeBase.h"
#include "DataAssetClasses/DA_InputActions.h"
#include "GameFramework/PlayerController.h"
#include "InterfaceClasses/ControllerInterface.h"
#include "InterfaceClasses/SoundInterface.h"
#include "UIClasses/PlayerHUD.h"
#include "InputController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyMenuOptionClickSignature, class UDA_BuildingAsset*, BuildingAsset);

UCLASS()
class TOWERDEFENCEGAME_API AInputController : public APlayerController, public IControllerInterface, public ISoundInterface
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsPaused;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controller Components")
	class UAudioComponent* LevelAudioComp;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UDA_InputActions* DA_Inputs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ASpecPlayer* SpecPawn;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	const UInputMappingContext* InputMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class AGameHUD* GameHUD;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class UPlayerHUD* PlayerHUD;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	ATowerDefenceGameGameModeBase* GameMode;


	AInputController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	template <typename T>
	void HUDUpdater(EHudValue ValueToUpdate, T Value)
	{
		PlayerHUD->Updater(ValueToUpdate, Value);
	};

	virtual void PlaySound_Implementation() override;
	virtual void StopSound_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ManageAudio(bool hasWaveStarted);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnBuyMenuOptionClickSignature OnBuyMenuOptionClickSignature;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuyOptionClicked(UDA_BuildingAsset* BuildingAsset);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Move(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Look(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EnableLook(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisableLook(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LeftMouseActions();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Zoom(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PauseGame();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SideWidgetToggler(class ABaseBuilding* BuildingRef = nullptr);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpgradeButtonClick(ABaseBuilding* BuildingToUpgrade, int UpgradeCost);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMoveButtonClick();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEnemyKilled();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGameComplete();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWaveStart();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWaveComplete(int WaveNumber);


};

