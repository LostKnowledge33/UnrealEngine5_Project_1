// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_SetSpeed.h"
#include "Global.h"
#include "Enemy/C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StatusComponent.h"



UC_BTTaskNode_SetSpeed::UC_BTTaskNode_SetSpeed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UC_BTTaskNode_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_StatusComponent* status = CHelpers::GetComponent<UC_StatusComponent>(ai);

	status->SetSpeed(SpeedType);

	return EBTNodeResult::Succeeded;
}
