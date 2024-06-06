// Copyright 2023 Harlan Cox. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BHP_ProjectileMovementComponent.generated.h"

class AActor;

// Delegate for when the projectile has missed its target. Called when the distance between the projectile and its target
// changes from decreasing to increasing. This can be used to trigger a "miss" effect, like exploding a missile at its closest
// proximity to the target or to notify the target that it dodged the projectile.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMissedTargetDelegate);

/**
 * BHP_ProjectileMovementComponent is a custom projectile movement component that overrides homing functionality to improve
 * homing performance and enable homing on any arbitrary point in space. It also provides utility functions for estimating
 * impact locations between a projectile and a moving target, and between a moving target and a projectile fired by a moving shooter. 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))

class BETTERHOMINGPROJECTILES_API UBHP_ProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:

	UBHP_ProjectileMovementComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Overridden to return true when bIsHomingActive is true.
	virtual bool ShouldUseSubStepping() const override;

	// Returns true when bIsHomingProjectile is true and the homing target was set in one of the following ways:
	// 1. HomingTargetComponent was set. 2. SetHomingPointOnActor was called. 3. SetHomingPointOffActor was called.
	UFUNCTION(BlueprintCallable, Category = "Homing")
	bool IsHomingActive() const;
	
	// Call this to set a specific HomingPoint attached to an actor.
	// Enter NewHomingPoint in world space. It will be transformed to the target's local space and will move with the actor. 
	// If TargetActor is null, the homing target will be cleared.
	UFUNCTION(BlueprintCallable, Category = "Homing")
	void SetHomingPointOnActor(AActor* TargetActor, const FVector& NewHomingPoint);

	// Call this to set a HomingPoint in world space, with no dependence on any actor.
	UFUNCTION(BlueprintCallable, Category = "Homing")
	void SetHomingPointOffActor(const FVector& NewHomingPoint);

	UFUNCTION(BlueprintCallable, Category = "Homing")
	void ClearHomingTarget();

	// Adds acceleration to the projectile.
	UFUNCTION(BlueprintCallable, Category = "Homing")
	void AddAcceleration(const FVector& Acceleration);
	
	// Estimates the impact location between a projectile and a moving target. Assumes constant target speed, constant
	// projectile speed, and no external forces like drag or gravity. Returns whether a valid impact location was found.
	UFUNCTION(BlueprintCallable, Category = "Homing")
	static bool EstimateImpactLocation(FVector& OutImpactLocation, const FVector& ProjectileLocation, const float ProjectileSpeed, const FVector& TargetLocation, const FVector& TargetVelocity);

	// Estimates the impact location between a moving target and a projectile fired by a moving shooter, assuming the projectile inherits
	// the shooter's velocity upon firing. Also assumes constant target speed, constant projectile speed, and no external forces like drag or gravity.
	// Returns whether a valid impact location was found.
	UFUNCTION(BlueprintCallable, Category = "Homing")
	static bool EstimateFiringSolution(FVector& OutImpactLocation, const FVector& ShooterLocation, const FVector& ShooterVelocity, const FVector& TargetLocation, const FVector& TargetVelocity, const float ProjectileSpeed);

	// Broadcasts when the projectile stops getting closer to the HomingPoint and starts getting further away.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Homing")
	FOnMissedTargetDelegate OnMissedHomingTarget;
	
	// This value determines how aggressively the projectile will use its available homing acceleration to respond to
	// the target's maneuvers. Higher values result in more aggressive maneuvering toward target intercept.
	// Value of 1 results in pure pursuit, in which the projectile does not lead the target. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing", meta = (ClampMin = "1.0"))
	float ProportionalNavigationGain = 5.f;

	// If true, the projectile will speed up or slow down as needed to maximize the chance of hitting the target.
	// True is recommended for powered projectiles like missiles.
	// If false, homing acceleration will be applied to change the direction of the projectile's velocity, but not its magnitude.
	// False is recommended for unpowered projectiles like guided bombs.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing")
	bool bCanHomingChangeSpeed = true;
	
protected:

	void UpdateHomingPoint();
	
	virtual FVector ComputeAcceleration(const FVector& InVelocity, float DeltaTime) const override;
	
	virtual FVector ComputeHomingAcceleration(const FVector& InVelocity, float DeltaTime) const override;

	void CheckForMissedTarget(const float ClosureRate) const;

	// Returns an acceleration that is perpendicular to the velocity. Used when bCanHomingChangeSpeed == false.
	virtual FVector ComputePureProNavAcceleration(const FVector& InVelocity) const;

	// Returns an acceleration that is perpendicular to the line of sight and the line of sight rotation axis. Used when bCanHomingChangeSpeed == true.
	virtual FVector ComputeTrueProNavAcceleration(const FVector& InVelocity, const float InClosureRate) const;

	// The point in world space the projectile will home in on.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	FVector HomingPoint = FVector::ZeroVector;
	
	// The HomingPoint's linear velocity.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	FVector HomingPointVelocity = FVector::ZeroVector;
	
	// The unit vector defining the direction from the projectile to the Homing Point.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	FVector LineOfSightAxis = FVector::ZeroVector;

	// The line of sight axis of rotation from the previous frame to the current frame.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	FVector LineOfSightRotationAxis = FVector::ZeroVector;

	// The angular rate of change of the LineOfSight
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	float LineOfSightAngularSpeed = 0.f;
	
	// Target actor to home in on. Non-null when the homing target was set via SetHomingPointOnActor. Null otherwise.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	TWeakObjectPtr<AActor> HomingTargetActor = nullptr;
	
	// Defines the HomingPoint position, relative to the HomingTargetActor.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	FVector HomingPointLocalOffset = FVector::ZeroVector;
	
	// If true, SetHomingPointOffActor was called to set the homing point to a specific point in world space, not relative to any actor.
	UPROPERTY(BlueprintReadOnly, Category = "Homing")
	bool bHomingPointOffActor = false;

private:

	bool bHomingActiveThisUpdate = false;

	FVector PreviousHomingPoint = FVector::ZeroVector;

	FVector PreviousLineOfSight = FVector::ZeroVector;

	bool bTransformLocalOffset = false;
	
	mutable bool bPreviousClosureRatePositive = false;

};