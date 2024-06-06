// Copyright 2023 Harlan Cox. All Rights Reserved.

#include "BHP_ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"

UBHP_ProjectileMovementComponent::UBHP_ProjectileMovementComponent()
{
	bIsHomingProjectile = true;
}

void UBHP_ProjectileMovementComponent::SetHomingPointOnActor(AActor* TargetActor, const FVector& NewHomingPoint)
{
	ClearHomingTarget();
	
	if (TargetActor != nullptr)
	{
		HomingTargetActor = TargetActor;
		HomingPointLocalOffset = TargetActor->GetTransform().InverseTransformPosition(NewHomingPoint);
		bTransformLocalOffset = !HomingPointLocalOffset.IsNearlyZero(1.f); // 1 cm is close enough
	}
}

void UBHP_ProjectileMovementComponent::SetHomingPointOffActor(const FVector& NewHomingPoint)
{
	ClearHomingTarget();
	
	bHomingPointOffActor = true;
	HomingPoint = NewHomingPoint;
}

void UBHP_ProjectileMovementComponent::ClearHomingTarget()
{
	HomingTargetComponent = nullptr;
	HomingTargetActor = nullptr;
	HomingPoint = FVector::ZeroVector;
	HomingPointLocalOffset = FVector::ZeroVector;
	bTransformLocalOffset = false;
	bHomingPointOffActor = false;
}

void UBHP_ProjectileMovementComponent::AddAcceleration(const FVector& Acceleration)
{
	// AddForce from parent PMC adds force as acceleration (mass has no effect). See parent ComputeAcceleration function where Acceleration += PendingForceThisUpdate;
	AddForce(Acceleration);
}

bool UBHP_ProjectileMovementComponent::EstimateImpactLocation(FVector& OutImpactLocation, const FVector& ProjectileLocation,
const float ProjectileSpeed, const FVector& TargetLocation, const FVector& TargetVelocity)
{
	if (TargetVelocity.IsNearlyZero())
	{
		if (ProjectileSpeed > 0.f)
		{
			OutImpactLocation = TargetLocation;
			return true;
		}

		// Projectile and target are both stationary
		return false;
	}

	// Target is moving and projectile is stationary (unlikely case, but possible)
	if (ProjectileSpeed <= 0.f)
	{
		FVector LineOfSight = ProjectileLocation - TargetLocation;

		// The target is moving toward the stationary projectile and will hit it at the projectile's location.
		if (FMath::IsNearlyZero(FMath::Acos(TargetVelocity.Dot(LineOfSight) / TargetVelocity.Size() / LineOfSight.Size())))
		{
			OutImpactLocation = ProjectileLocation;
			return true;
		}
		return false;
	}

	// Solution is quadratic of the form a*t^2 + b*t + c = 0;
	const FVector LineOfSight = TargetLocation - ProjectileLocation;
	const float A = FVector::DotProduct(TargetVelocity, TargetVelocity) - FMath::Square(ProjectileSpeed);
	const float B = FVector::DotProduct(LineOfSight, TargetVelocity) * 2.f;
	const float C = FVector::DotProduct(LineOfSight, LineOfSight);
	const float D = B * B - 4 * A * C;

	// no real solution
	if (D < 0.f) return false;
	
	const float SqrtD = FMath::Sqrt(D);
	const float Solution1 = (-B + SqrtD) / (2.f * A);
	const float Solution2 = (-B - SqrtD) / (2.f * A);
	
	float TimeToImpact = -1.f; // Initialize with an invalid time
	if (Solution1 > 0.f && (Solution1 < Solution2 || Solution2 <= 0.f))
	{
		TimeToImpact = Solution1;
	}
	else if (Solution2 > 0.f)
	{
		TimeToImpact = Solution2;
	}
	if (TimeToImpact < 0.f) return false;

	OutImpactLocation = TargetLocation + TargetVelocity * TimeToImpact;
	return true;
}

bool UBHP_ProjectileMovementComponent::EstimateFiringSolution(FVector& OutImpactLocation, const FVector& ShooterLocation,
const FVector& ShooterVelocity, const FVector& TargetLocation, const FVector& TargetVelocity, const float ProjectileSpeed)
{
	const FVector RelativeVelocity = TargetVelocity - ShooterVelocity;
	return EstimateImpactLocation(OutImpactLocation, ShooterLocation, ProjectileSpeed, TargetLocation, RelativeVelocity);
}

void UBHP_ProjectileMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// TRACE_CPUPROFILER_EVENT_SCOPE(STAT_BHP_ProjectileMovementComponent_TickComponent);
	// TRACE_BOOKMARK(TEXT("BHP_ProjectileMovementComponent_TickComponent"))

	bHomingActiveThisUpdate = IsHomingActive();
	if (bHomingActiveThisUpdate)
	{
		UpdateHomingPoint();
		
		// Estimate the HomingPoint's velocity. The first frame will result in an invalid velocity, but the PreviousLineOfSight
		// will also be zero resulting in zero LineOfSightRotationAxis and zero ProNav homing acceleration. Therefore, no
		// correction is required to account for the incorrect velocity on the first frame. 
		HomingPointVelocity = (HomingPoint - PreviousHomingPoint) / DeltaTime;
		PreviousHomingPoint = HomingPoint;
	
		// The target's location is updated in tick, but not in substeps, so we must compute the line of sight rate in tick and not in
		// ComputeAcceleration, which is called every substep. Attempting to calculate the LOS rate in substeps produces incorrect results.
		const FVector PreviousLineOfSightAxis = PreviousLineOfSight.GetSafeNormal();
		const FVector LineOfSight = HomingPoint - UpdatedComponent->GetComponentLocation();
		LineOfSightAxis = LineOfSight.GetSafeNormal();
		LineOfSightAngularSpeed = FMath::Acos(FVector::DotProduct(LineOfSightAxis, PreviousLineOfSightAxis)) / DeltaTime;
		LineOfSightRotationAxis = FVector::CrossProduct(PreviousLineOfSightAxis, LineOfSightAxis).GetSafeNormal();
		PreviousLineOfSight = LineOfSight;
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBHP_ProjectileMovementComponent::ShouldUseSubStepping() const
{
	return bForceSubStepping || GetGravityZ() != 0.f || bHomingActiveThisUpdate;
}

bool UBHP_ProjectileMovementComponent::IsHomingActive() const
{
	return bIsHomingProjectile && (HomingTargetComponent.IsValid() || HomingTargetActor.IsValid() || bHomingPointOffActor);
}

void UBHP_ProjectileMovementComponent::UpdateHomingPoint()
{
	if (HomingTargetComponent.IsValid())
	{
		HomingPoint = HomingTargetComponent->GetComponentLocation();
		return;
	}

	if (HomingTargetActor.IsValid())
	{
		if (bTransformLocalOffset)
		{
			HomingPoint = HomingTargetActor->GetTransform().TransformPosition(HomingPointLocalOffset);
		}
		else
		{
			HomingPoint = HomingTargetActor->GetActorLocation();
		}
	}
}

FVector UBHP_ProjectileMovementComponent::ComputeAcceleration(const FVector& InVelocity, float DeltaTime) const
{
	FVector Acceleration(FVector::ZeroVector);
	
	Acceleration.Z += GetGravityZ();
	
	Acceleration += PendingForceThisUpdate;
	
	if (bHomingActiveThisUpdate)
	{
		Acceleration += ComputeHomingAcceleration(InVelocity, DeltaTime);
	}
	return Acceleration;
}

FVector UBHP_ProjectileMovementComponent::ComputeHomingAcceleration(const FVector& InVelocity, float DeltaTime) const
{
	float ClosureRate = (InVelocity - HomingPointVelocity).Dot(LineOfSightAxis);

	CheckForMissedTarget(ClosureRate);
	
	if (bCanHomingChangeSpeed)
	{
		// We're getting further away from the target, so accelerate toward it.
		if (ClosureRate <= 0.f) return LineOfSightAxis * HomingAccelerationMagnitude;
		
		// Returns acceleration perpendicular to the line of sight and the line of sight rotation axis.
		FVector HomingAcceleration = ComputeTrueProNavAcceleration(InVelocity, ClosureRate);
		
		const float TrueProNavAccelerationSizeSquared = HomingAcceleration.SizeSquared();
		const float HomingAccelerationMagnitudeSquared = FMath::Square(HomingAccelerationMagnitude);
		
		// If the acceleration perpendicular to the line of sight is less than the HomingAccelerationMagnitude,
		// then we can add acceleration in the direction of the line of sight to help accelerate toward the target.
		// This serves 2 functions:
		// 1. It helps increase speed when initial speed < max speed and when speed was lost during hard turns.
		// 2. It generally improves homing performance by making full use of the HomingAccelerationMagnitude we have available. 
		if (TrueProNavAccelerationSizeSquared < HomingAccelerationMagnitudeSquared)
		{
			// (acceleration perpendicular to LOS) + (acceleration parallel to LOS) <= HomingAccelerationMagnitude.
			HomingAcceleration += FMath::Sqrt(HomingAccelerationMagnitudeSquared - TrueProNavAccelerationSizeSquared) * LineOfSightAxis;
		}
		
		return HomingAcceleration;

		// Note: If the acceleration component along the LOS is large, the projectile may not appear to lead the target
		// as much as usual. This is acceptable because the ProNav acceleration always has priority and will attempt to
		// nullify any non-zero line of sight rate. Despite the difference in flight path, the added acceleration along
		// the LOS improves overall homing performance (decreases time to impact and increases probability of impact).
	}
	
	// Returns an acceleration that is perpendicular to the velocity, not line of sight.
	return ComputePureProNavAcceleration(InVelocity);
}

void UBHP_ProjectileMovementComponent::CheckForMissedTarget(const float ClosureRate) const
{
	if (bPreviousClosureRatePositive && ClosureRate < 0.f)
	{
		OnMissedHomingTarget.Broadcast();
	}
	bPreviousClosureRatePositive = ClosureRate > 0.f;
}

FVector UBHP_ProjectileMovementComponent::ComputePureProNavAcceleration(const FVector& InVelocity) const
{
	const FVector AccelerationDirection = FVector::CrossProduct(LineOfSightRotationAxis, InVelocity).GetSafeNormal();
	const float AccelerationMagnitude = FMath::Clamp(ProportionalNavigationGain * LineOfSightAngularSpeed * InVelocity.Size(), 0.f, HomingAccelerationMagnitude);
	
	return AccelerationMagnitude * AccelerationDirection;
}

FVector UBHP_ProjectileMovementComponent::ComputeTrueProNavAcceleration(const FVector& InVelocity, const float InClosureRate) const
{
	const FVector AccelerationDirection = FVector::CrossProduct(LineOfSightRotationAxis, LineOfSightAxis);
	const float AccelerationMagnitude = FMath::Clamp(ProportionalNavigationGain * LineOfSightAngularSpeed * InClosureRate, 0.f, HomingAccelerationMagnitude);
	
	return AccelerationMagnitude * AccelerationDirection;
}
