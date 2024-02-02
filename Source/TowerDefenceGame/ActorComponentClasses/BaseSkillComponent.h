// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class TOWERDEFENCEGAME_API UBaseSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseSkillComponent();

		
};
