// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "TowerDefenceGame/ActorComponentClasses/HealthComponent.h"
#include "TowerDefenceGame/UIClasses/HealthBarWidget.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	mHealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Comp");

	mHealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Health Bar Comp");
	mHealthBarWidgetComponent->SetupAttachment(RootComponent);
	mHealthBarWidgetComponent->SetDrawSize(WidgetDrawSize);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ABaseEnemy::IA_EnemyMove_Implementation(FVector TargetLocation)
{
	
}

void ABaseEnemy::IA_EnemyAttack_Implementation()
{
	
}

void ABaseEnemy::Init_Implementation()
{
	mHealthWidget = Cast<UHealthBarWidget>(mHealthBarWidgetComponent->GetWidget());
}
