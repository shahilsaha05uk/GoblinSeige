// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefenceGame/ActorComponentClasses/HealthComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
	mRangeComponent = CreateDefaultSubobject<USphereComponent>("Range Comp");
	RootComponent = mRangeComponent;
	
	mHealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Comp");
	
	mHealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Health Bar Comp");
	mHealthBarWidgetComponent->SetupAttachment(RootComponent);
	mHealthBarWidgetComponent->SetDrawSize(WidgetDrawSize);
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AInteractableActor::Init_Implementation()
{
	mHealthWidget = Cast<UHealthBarWidget>(mHealthBarWidgetComponent->GetWidget());
}
