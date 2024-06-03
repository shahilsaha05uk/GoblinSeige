// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"
#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>
#include "Camera/CameraComponent.h"
#include "GameFramework/HUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/ActorComponentClasses/BuildingPlacementHandlerComponent.h"
#include "TowerDefenceGame/ActorComponentClasses/TimerComponent.h"
#include "TowerDefenceGame/ControllerClasses/InputController.h"
#include "TowerDefenceGame/InterfaceClasses/HUDInterface.h"

ASpecPlayer::ASpecPlayer()
{
	mSpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	mSpringArmComp->SetupAttachment(RootComponent);

	mCameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	mCameraComp->SetupAttachment(mSpringArmComp);
	
	mBuildingPlacementHandlerComponent = CreateDefaultSubobject<UBuildingPlacementHandlerComponent>("PlayerInteractionComponent");
	
	OrbitRadius = 300.0f;
	OrbitSpeed = 50.0f;
	CurrentAngle = 0.0f;

	MinPitchAngle = -30.0f;
	MaxPitchAngle = 89.0f;
}


void ASpecPlayer::PossessedBy(AController* NewController)	// Called before BeginPlay
{
	Super::PossessedBy(NewController);

	ControllerRef = Cast<AInputController>(NewController);

	// Binding to the events inside the subsystems
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
		GameSubs->OnHudInitialised.AddDynamic(this, &ThisClass::OnHudInitialised);

	// Orbit setup
	if(mOrbitActorClass)
	{
		mOrbitActor = UGameplayStatics::GetActorOfClass(GetWorld(), mOrbitActorClass);
	}
	if(mOrbitActor)
	{
		mOrbitCenter = mOrbitActor->GetActorLocation();
	}

	CalculateInitialAngles();
	UpdateCameraPosition();
}

void ASpecPlayer::OnHudInitialised(AHUD* HudRef)
{
	if(UKismetSystemLibrary::DoesImplementInterface(HudRef, UHUDInterface::StaticClass()))
	{
		mPlayerHUD = Cast<UPlayerHUD>(IHUDInterface::Execute_GetWidgetReference(HudRef, PLAYER_HUD));
	}
}

#pragma region Input

void ASpecPlayer::Move_Implementation(const FInputActionValue& InputActionValue)
{
	/*
	const FVector vec = InputActionValue.Get<FVector>();

	const FRotator cachedRot = GetControlRotation();
	
	FRotator fwdRot = cachedRot; fwdRot.Roll = fwdRot.Pitch = 0;
	FRotator rhtRot = cachedRot; rhtRot.Pitch = 0;
	
	const FVector fwdVec = fwdRot.Vector();
	const FVector rhtVec = FRotationMatrix(rhtRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(fwdVec, vec.X);
	AddMovementInput(rhtVec, vec.Y);
*/
}

void ASpecPlayer::Look_Implementation(const FInputActionValue& InputActionValue)
{
	const FVector2D LookInput = InputActionValue.Get<FVector2D>();

	const float Yaw = LookInput.X;
	const float Pitch = LookInput.Y;

	mCurrentYawAngle += Yaw * OrbitSpeed * GetWorld()->GetDeltaSeconds();
	if (mCurrentYawAngle >= 360.0f)
	{
		mCurrentYawAngle -= 360.0f;
	}
	else if (mCurrentYawAngle < 0.0f)
	{
		mCurrentYawAngle += 360.0f;
	}
	
	mCurrentPitchAngle += Pitch * OrbitSpeed * GetWorld()->GetDeltaSeconds();
	mCurrentPitchAngle = FMath::Clamp(mCurrentPitchAngle, MinPitchAngle, MaxPitchAngle);

	UpdateCameraPosition();
}

void ASpecPlayer::EnableLook_Implementation()
{
}

void ASpecPlayer::DisableLook_Implementation()
{
}

void ASpecPlayer::LeftMouseActions_Implementation()
{
	mBuildingPlacementHandlerComponent->HandleInteraction();
}

void ASpecPlayer::Zoom_Implementation(float Value)
{
	
}

#pragma endregion

void ASpecPlayer::CalculateInitialAngles()
{
	FVector Direction = GetActorLocation() - mOrbitCenter;
	Direction.Normalize();

	mCurrentYawAngle = FMath::Atan2(Direction.Y, Direction.X) * (180.0f / PI);
	mCurrentPitchAngle = FMath::Asin(Direction.Z) * (180.0f / PI);
	mCurrentPitchAngle = FMath::Clamp(mCurrentPitchAngle, MinPitchAngle, MaxPitchAngle);
}

void ASpecPlayer::UpdateCameraPosition()
{
	const float RadYaw = FMath::DegreesToRadians(mCurrentYawAngle);
	const float RadPitch = FMath::DegreesToRadians(mCurrentPitchAngle);
	
	const FVector NewLocation = mOrbitCenter + FVector(FMath::Cos(RadYaw) * OrbitRadius, FMath::Sin(RadYaw) * OrbitRadius, FMath::Sin(RadPitch) * OrbitRadius);
	const FRotator NewRotation = (mOrbitCenter - NewLocation).Rotation();

	SetActorLocationAndRotation(NewLocation, NewRotation);
}
