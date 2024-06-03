// Fill out your copyright notice in the Description page of Project Settings.


#include "GetTheClosestSpline.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefenceGame/Actors/Spline.h"
#include "TowerDefenceGame/InterfaceClasses/TargetInterface.h"

EBTNodeResult::Type UGetTheClosestSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (const APawn* Pawn = Controller->GetPawn())
		{
			if (auto const BlackboardComp = OwnerComp.GetBlackboardComponent())
			{
				TArray<AActor*> Targets;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), SplineClass, Targets);

				if (Targets.Num() > 0)
				{
					float Distance = 0.0f;

					if (auto const Target = UGameplayStatics::FindNearestActor(Pawn->GetActorLocation(), Targets, Distance))
					{
						if (auto const Spline = Cast<ASpline>(Target))
						{
							BlackboardComp->SetValueAsObject(SplineRef.SelectedKeyName, Spline);
							return EBTNodeResult::Succeeded;
						}
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;}
