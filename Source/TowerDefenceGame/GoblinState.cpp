// Fill out your copyright notice in the Description page of Project Settings.


#include "GoblinState.h"

#include "SubsystemClasses/ResourceSubsystem.h"

void AGoblinState::BeginPlay()
{
	Super::BeginPlay();

	if(const auto ResourceSubs = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>())
	{
		ResourceSubs->Set(mStartingResources);
	}
}
