// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_Action.h"
#include "Global.h"
#include "Enemy/C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StateComponent.h"
#include "Components/C_ActionComponent.h"
#include "Player/C_ActionProcess.h"

UC_BTTaskNode_Action::UC_BTTaskNode_Action()
{
	bNotifyTick = true;

	NodeName = "Action";
}

void UC_BTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(ai);

	TotalTime += DeltaSeconds;

	if (TotalTime > Delay)
	{
		behavior->ChangeType(EBehaviorType::Strafe);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UC_BTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_ActionComponent* action = CHelpers::GetComponent<UC_ActionComponent>(ai);
	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(ai);

	TotalTime = 0.f;

	action->ActionProcess->DoAction();	
	
	return EBTNodeResult::InProgress;
}
