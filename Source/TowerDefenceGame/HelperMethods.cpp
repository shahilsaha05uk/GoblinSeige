// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperMethods.h"

#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"

void UHelperMethods::GetMouseLocation(APlayerController* Controller, FVector& MouseLocation)
{
	Controller->GetMousePosition(MouseLocation.X, MouseLocation.Y);
}

void UHelperMethods::GetMouseTrace(APlayerController* Controller, ETraceTypeQuery TraceQuery, bool& Value,
                                   FHitResult& hit)
{
	Value = Controller->GetHitResultUnderCursorByChannel(TraceQuery, true, hit);
}

void UHelperMethods::CalculateSnappedPosition(FVector HitLocation, float SnapInterval, FVector& SnappedPosition)
{
	SnappedPosition = FVector::ZeroVector;
	SnappedPosition.X = FMath::RoundToFloat(HitLocation.X / SnapInterval) * SnapInterval;
	SnappedPosition.Y = FMath::RoundToFloat(HitLocation.Y / SnapInterval) * SnapInterval;
	SnappedPosition.Z = HitLocation.Z; // Assuming Z remains as is, adjust if needed
}

float UHelperMethods::GetDotProductBetweenComponentWorldLocationAndActorLocation(USceneComponent* Component, AActor* Actor)
{
	return UKismetMathLibrary::Dot_VectorVector(Component->GetForwardVector(), Actor->GetActorLocation());
}

FString UHelperMethods::GetDescription(FBuildingStats stats)
{
	return FString::Printf(TEXT("Damage: %.1f\n"
									"Range: %.1f\n"
									"Speed: %.1f\n"),
									stats.AttackDamage,
									stats.AttackRange,
									stats.AttackSpeed);
}

FString UHelperMethods::GetUpgradeDescription(FBuildingStats CurrentStats, FBuildingStats UpgradeStats)
{
	return FString::Printf(TEXT("Damage: %.1f + %.1f\n"
								"Range: %.1f + %.1f\n"
								"Speed: %.1f + %.1f\n"),
								CurrentStats.AttackDamage, UpgradeStats.AttackDamage,
								CurrentStats.AttackRange, UpgradeStats.AttackRange,
								CurrentStats.AttackSpeed, UpgradeStats.AttackSpeed);
}

