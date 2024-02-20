// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumClass.generated.h"

UENUM(BlueprintType)
enum EHudValue
{
	MONEY_VALUE,
	WAVE_VALUE,
	UPGRADE_BUTTON_ENABLE
};

UENUM(BlueprintType)
enum EWidgetType
{
	NO_WIDGET,
	PLAYER_HUD,
	MAIN_MENU,
	SETTINGS,
	INSTRUCTION,
	PAUSE_MENU,
	GAMECOMPLETE_MENU
	
};
UENUM(BlueprintType)
enum ELevelToTravel
{
	NoLevelToTravel,
	GameLevel,
	MainMenuLevel
	
};
UENUM(BlueprintType)
enum ELevel
{
	NO_LEVEL,
	INITIAL_LEVEL,
	CURRENT_LEVEL,
	FINAL_LEVEL
};

UENUM(BlueprintType)
enum EBuildingState
{
	NO_STATE,
	PLACING,
	PLACED,
	SELECTED,
	DESELECTED,
	DESTROYED
};

UENUM(BlueprintType)
enum EPlacementMaterial
{
	NO_MATERIAL,
	VALID_MATERIAL,
	INVALID_MATERIAL,
	SELECTED_MATERIAL
};

UENUM(BlueprintType)
enum EControllerAllocation
{
	NO_CONTROLLER,
	AVAILABLE_CONTROLLER,
	ALLOCATED_CONTROLLER
};

UENUM(BlueprintType)
enum EManagerType
{
	ENEMY_MANAGER,
	WAVE_MANAGER
};

UENUM(BlueprintType)
enum ESideMenuSwitcher
{
	BUY_MENU,
	BUILDING_SETTINGS
};

UCLASS()
class TOWERDEFENCEGAME_API UEnumClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
