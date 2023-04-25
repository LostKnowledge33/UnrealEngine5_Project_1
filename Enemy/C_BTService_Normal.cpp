// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_BTService_Normal.h"
#include "Global.h"
#include "Player/C_Character.h"
#include "Enemy/C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StateComponent.h"
#include "Components/C_PatrolComponent.h"
#include "Components/C_StatusComponent.h"
#include "UE_ProjectGameModeBase.h"

UC_BTService_Normal::UC_BTService_Normal()
{
	NodeName = "Normal";
}

void UC_BTService_Normal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Cast<AUE_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetIntroState()) return;

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);

	AC_Enemy_AI* ai = Cast<AC_Enemy_AI>(controller->GetPawn());
	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(ai);
	UC_StatusComponent* status = CHelpers::GetComponent<UC_StatusComponent>(ai);
	UC_PatrolComponent* patrol = CHelpers::GetComponent<UC_PatrolComponent>(ai);

	if (!status->CanMove()) return;
	if (state->IsDeadMode()) return;

	if (state->IsHittedMode())
	{
		behavior->ChangeType(EBehaviorType::Hitted);
		return;
	}

	AC_Character* target = behavior->GetTargetPlayer();

	if (target == nullptr)
	{	
		if (patrol != nullptr && patrol->IsVaild())
		{
			behavior->ChangeType(EBehaviorType::Patrol);
			return;
		}
		
		behavior->ChangeType(EBehaviorType::Wait);
		return;
	}
	else
	{
		UC_StateComponent* targetState = CHelpers::GetComponent<UC_StateComponent>(target);
		if (targetState->IsDeadMode())
		{
			behavior->ChangeType(EBehaviorType::Wait);
			return;
		}
	}

	float distance = ai->GetDistanceTo(target);

	if (distance < controller->GetBehaviorRange())
	{
		FVector start = ai->GetActorLocation();
		FVector end = target->GetActorLocation();
		FVector direction = start - end;

		ai->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, end));
		
		behavior->ChangeType(EBehaviorType::Action);
		return;
	}

	if (distance < controller->GetSightRadius())
	{
		behavior->ChangeType(EBehaviorType::Approach);
		return;
	}
}
