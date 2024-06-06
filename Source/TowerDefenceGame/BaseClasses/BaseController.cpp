// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AudioComponent.h"


ABaseController::ABaseController()
{
	mAudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	mAudioComp->SetupAttachment(RootComponent);
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ABaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {

		BindControls(EnhancedInputComponent);
	}
}

void ABaseController::BindControls_Implementation(UEnhancedInputComponent* EnhancedInputComponent)
{
	
}


void ABaseController::Init_Implementation()
{
	InitSound();
}

void ABaseController::InitSound_Implementation()
{
}

