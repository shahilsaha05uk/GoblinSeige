#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UMainMenu : public UBaseWidget
{
	GENERATED_BODY()

public:

	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//class UButton* btnNewGame;
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//class UButton* btnSettings;
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//class UButton* btnInstructions;
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	//class UButton* btnQuit;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnNewGameClicked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSettingsClicked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnInstructionsClicked();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnQuitClicked();
};
