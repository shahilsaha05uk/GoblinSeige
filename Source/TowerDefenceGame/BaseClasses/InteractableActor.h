// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenceGame/InterfaceClasses/InteractableInterface.h"
#include "TowerDefenceGame/UIClasses/HealthBarWidget.h"
#include "InteractableActor.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class USphereComponent* mRangeComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UWidgetComponent* mHealthBarWidgetComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private Component")
	class UHealthComponent* mHealthComponent;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Private")
	FVector2D WidgetDrawSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Actor Properties")
	UHealthBarWidget* mHealthWidget;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init();
	
};
