// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_Enemy_AI_BossMonster.h"
#include "Global.h"
#include "Enemy/C_AIController.h"
#include "Components/C_StatusComponent.h"
#include "Components/C_ActionComponent.h"
#include "Player/C_ActionProcess.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"


AC_Enemy_AI_BossMonster::AC_Enemy_AI_BossMonster()
{
	CHelpers::GetClass<AC_AIController>(&AiClass, "/Script/Engine.Blueprint'/Game/BluePrints/BP_C_AIController.BP_C_AIController_C'");
	AIControllerClass = AiClass;

	CHelpers::CreateComponent<UCapsuleComponent>(this, &WeaponCollision, "WeaponCollision", GetMesh());

	GetStatus()->HealthProcess(100);
}

void AC_Enemy_AI_BossMonster::MyComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetAction()->GetWeaponCollisionState()) return;
	if (OtherActor == nullptr) return;
	if (this == OtherActor) return;
	if (OtherActor->GetClass() == this->GetClass()) return;

	GetAction()->ActionProcess->OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AC_Enemy_AI_BossMonster::MyComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetAction()->ActionProcess->OnComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AC_Enemy_AI_BossMonster::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy_AI_BossMonster::MyComponentBeginOverlap);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &AC_Enemy_AI_BossMonster::MyComponentEndOverlap);
}
