// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"

#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TowerDefenceGame/InterfaceClasses/EnemyControllerInterface.h"

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto ControllerRef = OwnerComp.GetAIOwner();

	if(UKismetSystemLibrary::DoesImplementInterface(ControllerRef, UEnemyControllerInterface::StaticClass()))
	{
		IEnemyControllerInterface::Execute_EnemyAttack(ControllerRef);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
