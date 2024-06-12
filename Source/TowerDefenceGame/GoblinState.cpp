// Fill out your copyright notice in the Description page of Project Settings.


#include "GoblinState.h"

#include "SubsystemClasses/GameSubsystem.h"
#include "SubsystemClasses/ResourceSubsystem.h"

void AGoblinState::BeginPlay()
{
	Super::BeginPlay();

	if(const auto GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		GameSubs->OnPhaseLoadedSuccessfully.AddDynamic(this, &ThisClass::OnPhaseLoaded);
	}

	mResourceSubsystem = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>();
	if(mResourceSubsystem)
	{
		mResourceSubsystem->Set(mStartingResources);
	}
}

void AGoblinState::OnPhaseLoaded_Implementation(int LoadedPhase, FPhaseDetails PhaseDetails)
{
	if(mResourceSubsystem)
	{
		mResourceSubsystem->AddPercentageOftheSpentMoney(PhaseDetails.TotalMoneyToAddBack);
	}
}
