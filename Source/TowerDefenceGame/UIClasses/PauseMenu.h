// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenceGame/BaseClasses/BaseWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UPauseMenu : public UBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnResume;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnReturnToMainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* btnQuit;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnResumeClicked();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnReturnToMainMenuClicked();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnQuitClicked();
};
