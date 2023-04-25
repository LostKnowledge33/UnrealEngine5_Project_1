// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_Patrol.h"
#include "Global.h"
#include "C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_PatrolComponent.h"

UC_BTTaskNode_Patrol::UC_BTTaskNode_Patrol()
{
	bNotifyTick = true;

	NodeName = "Patrol";
}

void UC_BTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_PatrolComponent* patrol = CHelpers::GetComponent<UC_PatrolComponent>(ai);

	FVector location;
	float acceptance;

	patrol->GetMoveTo(location, acceptance);
	EPathFollowingRequestResult::Type type = controller->MoveToLocation(location, acceptance, false);

	if (type == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (type == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		patrol->UpdateNextIndex();
	}
}

EBTNodeResult::Type UC_BTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_PatrolComponent* patrol = CHelpers::GetComponent<UC_PatrolComponent>(ai);

	FVector location;
	float acceptance;

	if (patrol->GetMoveTo(location, acceptance) == false)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}
