// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecPlayer.h"
#include <TowerDefenceGame/SubsystemClasses/GameSubsystem.h>
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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
	mColliderComp = CreateDefaultSubobject<UCapsuleComponent>("CollisionComp");
	RootComponent = mColliderComp;
	
	mSpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	mSpringArmComp->SetupAttachment(RootComponent);

	mCameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	mCameraComp->SetupAttachment(mSpringArmComp);
	
	mBuildingPlacementHandlerComponent = CreateDefaultSubobject<UBuildingPlacementHandlerComponent>("PlayerInteractionComponent");
	
	CurrentAngle = 0.0f;
}


void ASpecPlayer::PossessedBy(AController* NewController)	// Called before BeginPlay
{
	Super::PossessedBy(NewController);

	ControllerRef = Cast<AInputController>(NewController);

	// Binding to the events inside the subsystems
	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnHudInitialised.AddDynamic(this, &ThisClass::OnHudInitialised);
		GameSubs->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoaded);
	}
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
	const FVector vec = InputActionValue.Get<FVector>();

	const FRotator cachedRot = GetControlRotation();
	
	FRotator fwdRot = cachedRot; fwdRot.Roll = fwdRot.Pitch = 0;
	FRotator rhtRot = cachedRot; rhtRot.Pitch = 0;
	
	const FVector fwdVec = fwdRot.Vector() * MoveSpeed;
	const FVector rhtVec = FRotationMatrix(rhtRot).GetScaledAxis(EAxis::Y) * MoveSpeed;

	AddMovementInput(fwdVec, vec.X);
	AddMovementInput(rhtVec, vec.Y);
}

void ASpecPlayer::Look_Implementation(const FInputActionValue& InputActionValue)
{
	/*
	float yaw = InputActionValue.Get<FVector>().X;
	AddControllerYawInput(yaw);
	*/
	FVector2D LookInput = InputActionValue.Get<FVector2D>();

	// Yaw input
	float Yaw = LookInput.X;
	AddControllerYawInput(Yaw);

	// Pitch input
	float Pitch = LookInput.Y;
	AddControllerPitchInput(Pitch);
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

void ASpecPlayer::RecenterCamera_Implementation(FHitResult hit)
{
	
}

void ASpecPlayer::ShakeWhenInRange_Implementation()
{
	
}
#pragma endregion

void ASpecPlayer::OnPhaseLoaded_Implementation(int LoadedPhase, FPhaseDetails Details)
{
}

