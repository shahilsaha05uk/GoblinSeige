// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FollowTheSpline.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/Actors/Spline.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyControllerInterface.h"

EBTNodeResult::Type UBTT_FollowTheSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* ControllerRef = OwnerComp.GetAIOwner();
	auto const BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(UKismetSystemLibrary::DoesImplementInterface(ControllerRef, UEnemyControllerInterface::StaticClass()))
	{
		if(BlackboardComp)
		{
			if(ASpline* TargetActor = Cast<ASpline>(BlackboardComp->GetValueAsObject(SplineRef.SelectedKeyName)))
			{
				IEnemyControllerInterface::Execute_EnemyMove(ControllerRef, TargetActor);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
