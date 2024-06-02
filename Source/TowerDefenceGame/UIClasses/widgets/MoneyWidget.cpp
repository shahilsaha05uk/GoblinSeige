// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyWidget.h"

#include "Components/TextBlock.h"
#include "TowerDefenceGame/SubsystemClasses/ResourceSubsystem.h"

void UMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	if(const auto ResourceSubsystem = GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UResourceSubsystem>())
	{
		ResourceSubsystem->OnResourceUpdated.AddDynamic(this, &ThisClass::UpdateMoney);
		UpdateMoney(ResourceSubsystem->GetCurrentResources());
	}

}

void UMoneyWidget::UpdateMoney(int Value)
{
	txtMoney->SetText(FText::AsNumber(Value));
}
