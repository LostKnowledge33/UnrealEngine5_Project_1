// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/C_SpawnMonsterTrigger.h"
#include "Global.h"
#include "Enemy/C_Enemy.h"
#include "Enemy/C_Enemy_AI_NormalMonster.h"
#include "Enemy/C_AIController.h"
#include "Components/C_StatusComponent.h"

#include "Components/BoxComponent.h"

// Sets default values
AC_SpawnMonsterTrigger::AC_SpawnMonsterTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	CHelpers::GetClass<AC_Enemy_AI_NormalMonster>(&MonsterClass, "/Script/Engine.Blueprint'/Game/BluePrints/Enemy/BP_C_Enemy_AI_NormalMonster.BP_C_Enemy_AI_NormalMonster_C'");

	CHelpers::GetClass<AC_AIController>(&ttte, "/Script/Engine.Blueprint'/Game/BluePrints/BP_C_AIController.BP_C_AIController_C'");
}

void AC_SpawnMonsterTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC_SpawnMonsterTrigger::ActorBeginOverlap);
}

void AC_SpawnMonsterTrigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FTransform temp = GetActorTransform();
	temp.SetTranslation(GetActorLocation() + FVector(700, 0, 0));
	temp.SetRotation(FRotator(0, 180, 0).Quaternion());

	AC_Enemy_AI_NormalMonster* monster = GetWorld()->SpawnActor<AC_Enemy_AI_NormalMonster>(MonsterClass, temp);
	monster->GetStatus()->SetStop();
	monster->SpawnDefaultController();
	monster->SetActorHiddenInGame(false);
	monster->PlayAnimMontage(SpawnAnim);
	
	Destroy();
}
