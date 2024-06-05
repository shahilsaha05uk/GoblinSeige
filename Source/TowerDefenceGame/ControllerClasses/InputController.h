#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefenceGame/InterfaceClasses/ControllerInterface.h"
#include "TowerDefenceGame/InterfaceClasses/SoundInterface.h"
#include "TowerDefenceGame/SupportClasses/EnumClass.h"
#include "TowerDefenceGame/UIClasses/PlayerHUD.h"
#include "InputController.generated.h"


UENUM(BlueprintType)
enum EInputModeType { UI_Only, UI_And_Game, Game_Only };

class UDA_InputActions;
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyMenuOptionClickSignature, class UDA_BuildingAsset*, BuildingAsset);

UCLASS()
class TOWERDEFENCEGAME_API AInputController : public APlayerController, public IControllerInterface, public ISoundInterface
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsPaused;
	UPROPERTY(BlueprintReadOnly)
	class UPlayerHUD* mPlayerHUD;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class UDA_BuildingAsset* DA_UpgradeAsset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	UDA_InputActions* DA_Inputs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	class ASpecPlayer* SpecPawn;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	const UInputMappingContext* InputMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controller Components")
	class UAudioComponent* LevelAudioComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sounds")
	class USoundCue* WaveCue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private | Sounds")
	class USoundCue* BackgroundCue;


	AInputController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void PlaySound_Implementation() override;
	virtual void StopSound_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ManageAudio(bool hasWaveStarted);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPhaseComplete(int Phase);
	
	
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

	
	// Wave Methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGameComplete(bool bWon);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlacementUpdated(EPlacementState State, APlacementActor* PlacementActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPhaseLoadedSuccess(int LoadedPhase);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetInputMoveType(EInputModeType Type);
};

