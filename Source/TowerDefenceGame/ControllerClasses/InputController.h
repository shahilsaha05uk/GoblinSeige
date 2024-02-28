#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefenceGame/InterfaceClasses/ControllerInterface.h"
#include "TowerDefenceGame/InterfaceClasses/SoundInterface.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/UIClasses/PlayerHUD.h"
#include "InputController.generated.h"


class UDA_InputActions;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyMenuOptionClickSignature, class UDA_BuildingAsset*, BuildingAsset);

UCLASS()
class TOWERDEFENCEGAME_API AInputController : public APlayerController, public IControllerInterface, public ISoundInterface
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsPaused;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UDA_InputActions* DA_Inputs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ASpecPlayer* SpecPawn;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	const UInputMappingContext* InputMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class AGameHUD* GameHUD;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controller Components")
	class UAudioComponent* LevelAudioComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class UPlayerHUD* PlayerHUD;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ATowerDefenceGameGameModeBase* GameMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sounds")
	class USoundCue* WaveCue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sounds")
	class USoundCue* BackgroundCue;


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
	void RequestGameCompleteUI(bool hasWon);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ManageAudio(bool hasWaveStarted);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnBuyMenuOptionClickSignature OnBuyMenuOptionClickSignature;

	// Controller Input Methods
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetPlayerStartingBalance();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SideWidgetToggler(class ABaseBuilding* BuildingRef = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnBuyOptionClicked(UDA_BuildingAsset* BuildingAsset);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpgradeButtonClick(ABaseBuilding* BuildingToUpgrade, int UpgradeCost);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMoveButtonClick();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEnemyKilled();

	// Wave Methods
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGameComplete();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGameOver();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWaveStart();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWaveComplete(int WaveNumber);

};

