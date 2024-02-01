// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperMethods.h"

#include "NavigationSystem.h"

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

void UHelperMethods::IsPointerOnNavMesh(UWorld* world, float Tolerance, const FVector& Point, bool& Value)
{
	/*FVector ProjectedPoint;
	FNavLocation OutLocation;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(world);
	if (NavSys && NavSys->ProjectPointToNavigation(Point, OutLocation, FVector::ZeroVector))
	{
		ProjectedPoint = OutLocation.Location;
		// If the distance between the point and the projected point is small, it's on the NavMesh
		Value = FVector::DistSquared(Point, ProjectedPoint) < Tolerance * Tolerance;
	}
	Value = false;*/
}
