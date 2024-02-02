// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "DA_InputActions.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UDA_InputActions : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* IA_SpMove;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* IA_SpLook;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* IA_SpEnableLook;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* IA_LeftMouseActions;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* IA_Zoom;
};
