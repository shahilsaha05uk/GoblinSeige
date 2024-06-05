// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/ActorComponentClasses/HealthComponent.h"
#include "TowerDefenceGame/InterfaceClasses/TargetInterface.h"
#include "TowerDefenceGame/SubsystemClasses/GameSubsystem.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"
#include "TowerDefenceGame/UIClasses/HealthBarWidget.h"
#include "TowerDefenceGame/UIClasses/widgets/ParentBar.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	mHealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Comp");

	mHealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Health Bar Comp");
	mHealthBarWidgetComponent->SetupAttachment(RootComponent);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ABaseEnemy::Init_Implementation()
{
	mHealthComponent->OnHealthUpdated.AddDynamic(this, &ThisClass::OnHealthUpdated);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnemyBeginOverlap);
	
	mHealthWidget = Cast<UParentBar>(mHealthBarWidgetComponent->GetWidget());

	if(auto const GameSubs = GetGameInstance()->GetSubsystem<UGameSubsystem>())
		GameSubs->OnPhaseComplete.AddDynamic(this, &ThisClass::OnPhaseComplete);

}

#pragma region Interface Enemy Movement

void ABaseEnemy::IA_FollowTheSpline_Implementation(ASpline* Spline)
{
	
}

void ABaseEnemy::IA_EnemyAttack_Implementation()
{
	
}

#pragma endregion

#pragma region On Triggers

void ABaseEnemy::OnDeadAnimationEnd_Implementation()
{
	Destroy();
}

void ABaseEnemy::TakeRadiamDamage_Implementation()
{
	
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                             AController* EventInstigator, AActor* DamageCauser)
{
	mHealthComponent->DeductHealth(DamageAmount);

	return 0.0f;
}

void ABaseEnemy::OnHealthUpdated_Implementation(float CurrentHealth)
{
	if(CurrentHealth <= 0.0f)
	{
		mHealthComponent->OnHealthUpdated.Clear();

		// Reward money
		if(const auto LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
		{
			if(const auto mResourceSubsystem = LocalPlayer->GetSubsystem<UResourceSubsystem>())
				mResourceSubsystem->Add(AmountToReward);
		}
		// Die
		bIsDead = true;
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->StopMovementKeepPathing();

		GetController()->UnPossess();
	}
	if(mHealthWidget)
	{
		mHealthWidget->UpdateBar(CurrentHealth);
	}
}

void ABaseEnemy::OnEnemyBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UTargetInterface::StaticClass()) && OtherActor == mTarget) return;

	mTarget = OtherActor;

	// Setting the Blackboard key
	if(auto const blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this))
	{
		blackboard->SetValueAsObject(blackboard_Target, mTarget);
	}
}

void ABaseEnemy::OnAttackNotified_Implementation()
{
	// Applies damage when the enemy makes the damage animation
	UGameplayStatics::ApplyDamage(mTarget, mDealDamage, GetController(), this, nullptr);
}

#pragma endregion

void ABaseEnemy::OnPhaseComplete_Implementation(int Phase)
{
	Destroy();

}