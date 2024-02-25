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
	BUILDING_NAME_VALUE
};

UENUM(BlueprintType)
enum ESavedValue
{
	SOUND_SETTINGS
};

UENUM(BlueprintType)
enum ESoundValue
{
	NO_SOUND_VALUE,
	GAME_SOUND_VALUE,
	MENU_SOUND_VALUE,
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

UENUM(BlueprintType)
enum EButtonState
{
	BUTTON_ENABLED, BUTTON_DISABLED, BUTTON_HOVERED, BUTTON_UNHOVERED
};

UCLASS()
class TOWERDEFENCEGAME_API UEnumClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
