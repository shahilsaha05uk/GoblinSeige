// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API ABaseController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component")
	class UAudioComponent* mAudioComp;

	ABaseController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BindControls(class UEnhancedInputComponent* EnhancedInputComponent);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitSound();
};
