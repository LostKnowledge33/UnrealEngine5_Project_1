// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_Skill.h"
#include "Global.h"
#include "C_AIController.h"
#include "Enemy/C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StateComponent.h"
#include "Components/C_ActionComponent.h"
#include "Player/C_ActionProcess.h"
#include "Player/C_Character.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTaskNode_Skill::UC_BTTaskNode_Skill()
{
	bNotifyTick = true;

	NodeName = "Skill";
}

void UC_BTTaskNode_Skill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(ai);


	TotalTime += DeltaSeconds;

	if (TotalTime > Delay)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UC_BTTaskNode_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_ActionComponent* action = CHelpers::GetComponent<UC_ActionComponent>(ai);
	AC_Character* target = Cast<AC_Character>(controller->GetBlackboardComponent()->GetValueAsObject("Player"));
	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(ai);
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);

	float targetDiff = target->GetDistanceTo(ai);

	TotalTime = 0.f;

	if (targetDiff > 700.f)
	{
		action->ActionProcess->DoAction_Skill();
	}
	else
	{
		behavior->ChangeType(EBehaviorType::Approach);
		return EBTNodeResult::Succeeded;
	}
		

	return EBTNodeResult::InProgress;
}
