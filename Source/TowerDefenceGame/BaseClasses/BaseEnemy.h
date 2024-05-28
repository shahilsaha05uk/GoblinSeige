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

public:

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;
	
	// Sets default values for this character's properties
	ABaseEnemy();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UWidgetComponent* mHealthBarWidgetComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UHealthComponent* mHealthComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FVector2D WidgetDrawSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor Properties")
	class UHealthBarWidget* mHealthWidget;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPawnDeadSignature OnPawnDeadSignature;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init();


	virtual void IA_EnemyMove_Implementation(FVector TargetLocation) override;
	virtual void IA_EnemyAttack_Implementation() override;
	virtual bool isDead_Implementation() override { return false; }
};
