// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"

void ASpecPlayer::Move_Implementation(const FInputActionValue& InputActionValue)
{
}

void ASpecPlayer::Look_Implementation(const FInputActionValue& InputActionValue)
{
}

void ASpecPlayer::EnableLook_Implementation()
{
}

void ASpecPlayer::DisableLook_Implementation()
{
}

FVector ASpecPlayer::CalculateSnappedPosition(FVector HitLocation, float SnapInterval)
{
	FVector SnappedPosition;
	SnappedPosition.X = FMath::RoundToFloat(HitLocation.X / SnapInterval) * SnapInterval;
	SnappedPosition.Y = FMath::RoundToFloat(HitLocation.Y / SnapInterval) * SnapInterval;
	SnappedPosition.Z = HitLocation.Z; // Assuming Z remains as is, adjust if needed

	return SnappedPosition;
}

void ASpecPlayer::OnBuildingSpawn_Implementation(ABaseBuilding* NewBuilding)
{
	
}

