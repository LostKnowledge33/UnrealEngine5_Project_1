// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BTService_ShinbiWolf.h"
#include "Global.h"
#include "Player/C_Character.h"
#include "Enemy/C_AIController.h"
#include "Enemy/C_Enemy_AI.h"
#include "Components/C_BehaviorComponent.h"
#include "Components/C_StateComponent.h"
#include "Components/C_PatrolComponent.h"
#include "Components/C_StatusComponent.h"
#include "UE_ProjectGameModeBase.h"

UC_BTService_ShinbiWolf::UC_BTService_ShinbiWolf()
{
	NodeName = "Boss";
}

void UC_BTService_ShinbiWolf::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Cast<AUE_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetIntroState()) return;

	AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
	UC_BehaviorComponent* behavior = CHelpers::GetComponent<UC_BehaviorComponent>(controller);

	ACharacter* wolf = Cast<ACharacter>(controller->GetPawn());

	ACharacter* target = behavior->GetTarget();

	if (target == nullptr)
	{
		behavior->ChangeType(EBehaviorType::Wait);
		return;
	}
	else
	{
		float distance = wolf->GetDistanceTo(target);

		if (distance < controller->GetBehaviorRange())
		{
			UAnimMontage* attack;
			CHelpers::GetAssetDynamic<UAnimMontage>(&attack, "/Script/Engine.AnimMontage'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Shinbi_Wolf/Animations/Temp_Wolf_Attack_Montage.Temp_Wolf_Attack_Montage'");
			wolf->PlayAnimMontage(attack);
			return;
		}

		if (distance < controller->GetSightRadius())
		{
			behavior->ChangeType(EBehaviorType::Approach);
		}
	}
}