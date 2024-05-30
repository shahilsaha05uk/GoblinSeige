// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/ActorComponentClasses/HealthComponent.h"
#include "TowerDefenceGame/InterfaceClasses/TargetInterface.h"
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

void ABaseEnemy::Init_Implementation()
{
	mHealthWidget = Cast<UHealthBarWidget>(mHealthBarWidgetComponent->GetWidget());

	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnDamageTaken);

	mHealthComponent->OnHealthUpdated.AddDynamic(this, &ThisClass::OnHealthUpdated);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnemyBeginOverlap);
}

void ABaseEnemy::IA_EnemyMove_Implementation(FVector TargetLocation)
{
	
}

void ABaseEnemy::IA_FollowTheSpline_Implementation(ASpline* Spline)
{
	
}

void ABaseEnemy::IA_EnemyAttack_Implementation()
{
	
}

void ABaseEnemy::OnDamageTaken_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	mHealthComponent->DeductHealth(Damage);
}


void ABaseEnemy::OnHealthUpdated(float CurrentHealth)
{
	if(CurrentHealth <= 0.0f)
	{
		mHealthComponent->OnHealthUpdated.Clear();
		mHealthComponent->SetHealth(0.0f);

		// Die
		bIsDead = true;
	}
}

void ABaseEnemy::OnEnemyBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UTargetInterface::StaticClass()))
	{
		Target = OtherActor;
	}
}

void ABaseEnemy::OnAttackNotified_Implementation()
{
	UGameplayStatics::ApplyDamage(Target, mDealDamage, GetController(), this, nullptr);
}
