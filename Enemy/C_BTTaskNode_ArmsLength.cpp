// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_ArmsLength.h"
#include "Global.h"
#include "C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_PatrolComponent.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StatusComponent.h"
#include "Components/C_StateComponent.h"
#include "Player/C_Character.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTaskNode_ArmsLength::UC_BTTaskNode_ArmsLength()
{
	bNotifyTick = true;

	NodeName = "ArmsLength";
}

void UC_BTTaskNode_ArmsLength::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_PatrolComponent* patrol = CHelpers::GetComponent<UC_PatrolComponent>(ai);
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);
	UC_StatusComponent* status = CHelpers::GetComponent<UC_StatusComponent>(ai);
	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(ai);
	AC_Character* target = Cast<AC_Character>(controller->GetBlackboardComponent()->GetValueAsObject("Player"));

	if (target != nullptr)
	{
		float targetDiff = target->GetDistanceTo(ai);
		float distanceDiff = fDistance - targetDiff;
		
		if (distanceDiff > 0)
		{
			state->SetBackstepMode();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}

		if (FMath::Abs(distanceDiff) > 30.f)
			ai->AddMovementInput(ai->GetActorForwardVector() * -1, distanceDiff);
		else
			behavior->ChangeType(EBehaviorType::Strafe);
	}

	fTotalTime += DeltaSeconds;
	if (fTotalTime > fDelay)
	{
		fTotalTime = 0.f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UC_BTTaskNode_ArmsLength::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_StatusComponent* status = CHelpers::GetComponent<UC_StatusComponent>(ai);

	status->SetSpeed(ECharacterSpeed::RUN);

	return EBTNodeResult::InProgress;
}
