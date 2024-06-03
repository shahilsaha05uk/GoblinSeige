// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetTheClosestSpline.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCEGAME_API UGetTheClosestSpline : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SplineClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector SplineRef;


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
