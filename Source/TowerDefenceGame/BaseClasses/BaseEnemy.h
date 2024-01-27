// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyInterface.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ABaseEnemy : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class USphereComponent* mRangeComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UWidgetComponent* mHealthBarWidgetComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UHealthComponent* mHealthComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FVector2D WidgetDrawSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor Properties")
	class UHealthBarWidget* mHealthWidget;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init();
};
