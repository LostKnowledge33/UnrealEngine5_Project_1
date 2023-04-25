// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_Hitted.h"
#include "Global.h"
#include "Enemy/C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_BehaviorComponent.h"


UC_BTTaskNode_Hitted::UC_BTTaskNode_Hitted()
{
}

EBTNodeResult::Type UC_BTTaskNode_Hitted::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);

	behavior->ChangeType(EBehaviorType::Wait);

	return EBTNodeResult::Succeeded;
}
