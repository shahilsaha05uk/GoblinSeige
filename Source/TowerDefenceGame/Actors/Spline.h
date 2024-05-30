// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spline.generated.h"

UCLASS()
class TOWERDEFENCEGAME_API ASpline : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component")
	class USplineComponent* mSpline;

	ASpline();
};
