// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTTaskNode_Strafe.h"
#include "Global.h"
#include "C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_PatrolComponent.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StatusComponent.h"
#include "Player/C_Character.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTaskNode_Strafe::UC_BTTaskNode_Strafe()
{
	bNotifyTick = true;

	NodeName = "Strafe";
}

void UC_BTTaskNode_Strafe::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_PatrolComponent* patrol = CHelpers::GetComponent<UC_PatrolComponent>(ai);
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);
	UC_StatusComponent* status = CHelpers::GetComponent<UC_StatusComponent>(ai);
	AC_Character* target = Cast<AC_Character>(controller->GetBlackboardComponent()->GetValueAsObject("Player"));

	if(target != nullptr)
	{
		switch (iWhatDoState)
		{
		case 0:
			ai->AddMovementInput(ai->GetActorRightVector() * -1, 100);
			break;
		case 1:
			ai->AddMovementInput(ai->GetActorRightVector(), 100);
			break;
		case 2:
			behavior->ChangeType(EBehaviorType::Skill);
			break;
		case 3:
			behavior->ChangeType(EBehaviorType::ArmsLength);
			break;
		}
	}

	TotalTime += DeltaSeconds;
	if (TotalTime > Delay)
	{
		TotalTime = 0.f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UC_BTTaskNode_Strafe::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_StatusComponent* status = CHelpers::GetComponent<UC_StatusComponent>(ai);
	
	iWhatDoState = FMath::RandRange(0, 3);

	while (iWhatDoState == iBeforeState)
	{
		iWhatDoState = FMath::RandRange(0, 3);
	}

	iBeforeState = iWhatDoState;

	status->SetSpeed(ECharacterSpeed::STRAFE);

	return EBTNodeResult::InProgress;
}
