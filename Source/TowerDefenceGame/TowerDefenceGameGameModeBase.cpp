// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenceGameGameModeBase.h"



void ATowerDefenceGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	mPlayerController = NewPlayer;
}
