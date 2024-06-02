 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"
#include "BaseEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPawnDeadSignature);


UCLASS()
class TOWERDEFENCEGAME_API ABaseEnemy : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeRef;

	UPROPERTY(EditDefaultsOnly)
	float mDealDamage;
	UPROPERTY(EditDefaultsOnly)
	int AmountToReward;
public:

	UPROPERTY(BlueprintReadWrite)
	AActor* mTarget;
	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UWidgetComponent* mHealthBarWidgetComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UHealthComponent* mHealthComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor Properties")
	class UHealthBarWidget* mHealthWidget;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPawnDeadSignature OnPawnDeadSignature;
	
	ABaseEnemy();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init();
	
	// Interface Methods
	virtual void IA_EnemyMove_Implementation(FVector TargetLocation) override;
	virtual void IA_FollowTheSpline_Implementation(ASpline* Spline) override;
	virtual void IA_EnemyAttack_Implementation() override;

	virtual bool isDead_Implementation() override { return bIsDead; }

	virtual AActor* GetTarget_Implementation() override { return mTarget; }

	// When the Enemy takes any kind of damage
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// When the enemy overlaps the tower range
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEnemyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// when the Health Updates
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnHealthUpdated(float CurrentHealth);

	// When the enemy attacks
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnAttackNotified();

	// when the dead animation ends
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDeadAnimationEnd();
};
