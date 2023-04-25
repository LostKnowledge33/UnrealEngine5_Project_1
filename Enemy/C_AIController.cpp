// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_AIController.h"
#include "Global.h"
#include "Components/C_BehaviorComponent.h"
#include "Enemy/C_Enemy.h"
#include "Enemy/C_Enemy_AI.h"
#include "Player/C_Character.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"

AC_AIController::AC_AIController()
{
	PrimaryActorTick.bCanEverTick = true;

	Blackboard = Super::Blackboard;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	CHelpers::CreateActorComponent<UC_BehaviorComponent>(this, &Behavior, "Behavior");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

	/*
	Sight->SightRadius = SightRange;
	Sight->LoseSightRadius = 1000;
	Sight->PeripheralVisionAngleDegrees = 90;
	*/
	
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	bAllowStrafe = true;
}

void AC_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDrawDebug) return;

	FVector axis(0, 0, 1);
	FVector center = OwnerEnemy->GetActorLocation();
	FVector target, forward;

	if (bIsSightDebug)
	{
		center.Z += -50;

		FRotator temp = OwnerEnemy->GetActorRotation();
		temp.Yaw += 45.f;
		forward = UKismetMathLibrary::GetForwardVector(temp);

		target = (forward * SightRange) + OwnerEnemy->GetActorLocation();
		target.Z = center.Z;

		DrawDebugLine(GetWorld(), center, target, FColor::Green);

		temp.Yaw -= 90.f;
		forward = UKismetMathLibrary::GetForwardVector(temp);

		target = (forward * SightRange) + OwnerEnemy->GetActorLocation();
		target.Z = center.Z;

		DrawDebugLine(GetWorld(), center, target, FColor::Green);

		//DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 300, FColor::Green, false, -1.0f, 0, 0, FVector::RightVector, FVector::ForwardVector);
		DrawDebugCircle(GetWorld(), center, BehaviorRange, 300, FColor::Red, false, -1.0f, 0, 0, FVector::RightVector, FVector::ForwardVector);
	}

}

float AC_AIController::GetSightRadius()
{
	return Sight->SightRadius;
}

void AC_AIController::SetSightRange(float SightRadius, float LoseRadius, float Angle)
{
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = SightRadius;
	Sight->LoseSightRadius = LoseRadius;
	Sight->PeripheralVisionAngleDegrees = Angle;
}

void AC_AIController::BeginPlay()
{
	Super::BeginPlay();

}

void AC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerEnemy = Cast<AC_Enemy_AI>(InPawn);

	SetGenericTeamId(OwnerEnemy->GetTeamID());

	Perception->OnPerceptionUpdated.AddDynamic(this, &AC_AIController::OnPerceptionUpdated);

	UseBlackboard(OwnerEnemy->GetEnemyTree()->BlackboardAsset, Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(OwnerEnemy->GetEnemyTree());
}

void AC_AIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void AC_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	AC_Character* player = nullptr;
	AC_Enemy* enemy = nullptr;

	for (AActor* actor : actors)
	{
		player = Cast<AC_Character>(actor);

		if (player != nullptr)
		{
			Blackboard->SetValueAsObject("Player", player);
			SetFocus(player);

			if (!OwnerEnemy->bIsEngage && OwnerEnemy->ActorHasTag(FName("Boss")))
			{
				PlayEngage();
			}
			break;
		}

		enemy = Cast<AC_Enemy>(actor);

		if (enemy != nullptr)
		{
			Blackboard->SetValueAsObject("Target", enemy);
		}
	}

	
}
